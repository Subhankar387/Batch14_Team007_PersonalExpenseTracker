#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------- PART 1: constants, types, global lookup table ---------- */

#define MAX_EXPENSES 100
#define DESC_LEN     50
#define DATA_FILE    "expenses.txt"
#define WARN_RATIO   0.9          /* early-warning threshold: 90% */

typedef enum {
    FOOD,
    TRAVEL,
    BOOKS,
    ENTERTAINMENT,
    NUM_CATEGORIES               /* automatically equals 4 */
} Category;

static const char *categoryNames[NUM_CATEGORIES] = {
    "Food", "Travel", "Books", "Entertainment"
};

typedef struct {
    char     description[DESC_LEN];
    double   amount;
    Category category;
} Expense;

/* ---------- PART 2: function prototypes ---------- */

void   readLine(const char *prompt, char *buf, int size);
double readDouble(const char *prompt, double minExclusive);
int    readInt(const char *prompt, int min, int max);

void   showMenu(void);
void   addExpense(Expense expenses[], int *count);
void   listExpensesSorted(const Expense expenses[], int count);

double calculateTotal(const Expense expenses[], int count);
void   calculateCategoryTotals(const Expense expenses[], int count,
                               double totals[]);
int    findHighestCategory(const double totals[]);

void   displayBudgetStatus(double budget, double total);
void   displaySummary(const Expense expenses[], int count, double budget);

int    saveData(const char *filename, const Expense expenses[],
                int count, double budget);
int    loadData(const char *filename, Expense expenses[],
                int *count, double *budget);

/* ---------- PART 3: safe input helpers ---------- */

/* Reads one line of text, strips the trailing newline. */
void readLine(const char *prompt, char *buf, int size)
{
    printf("%s", prompt);
    if (fgets(buf, size, stdin) == NULL) {   /* EOF (Ctrl+D / end of pipe) */
        printf("\nInput ended. Exiting.\n");
        exit(1);
    }
    buf[strcspn(buf, "\n")] = '\0';          /* replace '\n' with '\0' */
}

/* Keeps asking until the user types a number greater than minExclusive. */
double readDouble(const char *prompt, double minExclusive)
{
    char   line[64];
    double value;

    while (1) {
        readLine(prompt, line, sizeof line);
        if (sscanf(line, "%lf", &value) == 1 && value > minExclusive) {
            return value;
        }
        printf("  Invalid input. Enter a number greater than %.2f.\n",
               minExclusive);
    }
}

/* Keeps asking until the user types an integer in [min, max]. */
int readInt(const char *prompt, int min, int max)
{
    char line[64];
    int  value;

    while (1) {
        readLine(prompt, line, sizeof line);
        if (sscanf(line, "%d", &value) == 1 && value >= min && value <= max) {
            return value;
        }
        printf("  Invalid input. Enter a whole number from %d to %d.\n",
               min, max);
    }
}

/* ---------- PART 4: menu ---------- */

void showMenu(void)
{
    printf("\n===== EXPENSE TRACKER =====\n");
    printf("1. Add expense\n");
    printf("2. View all expenses (highest first)\n");
    printf("3. Show summary\n");
    printf("4. Change monthly budget\n");
    printf("5. Save data\n");
    printf("6. Save and exit\n");
}

/* ---------- PART 5: record an expense ---------- */

void addExpense(Expense expenses[], int *count)
{
    if (*count >= MAX_EXPENSES) {            /* bounds check */
        printf("Expense list is full (%d max).\n", MAX_EXPENSES);
        return;
    }

    Expense e;                               /* build the record locally */

    readLine("Description: ", e.description, DESC_LEN);
    if (e.description[0] == '\0') {
        strcpy(e.description, "(no description)");
    }

    e.amount = readDouble("Amount: ", 0);

    printf("Categories:\n");
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        printf("  %d. %s\n", i + 1, categoryNames[i]);
    }
    int choice = readInt("Choose category: ", 1, NUM_CATEGORIES);

    switch (choice) {
        case 1:  e.category = FOOD;          break;
        case 2:  e.category = TRAVEL;        break;
        case 3:  e.category = BOOKS;         break;
        case 4:  e.category = ENTERTAINMENT; break;
        default: e.category = FOOD;          break;   /* unreachable */
    }

    expenses[*count] = e;                    /* struct copy into the array */
    (*count)++;                              /* update caller's counter */
    printf("Expense added.\n");
}

/* ---------- PART 6: list expenses, sorted with bubble sort ---------- */

void listExpensesSorted(const Expense expenses[], int count)
{
    if (count == 0) {
        printf("No expenses recorded yet.\n");
        return;
    }

    Expense sorted[MAX_EXPENSES];
    memcpy(sorted, expenses, count * sizeof(Expense));   /* sort a copy */

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (sorted[j].amount < sorted[j + 1].amount) {
                Expense temp   = sorted[j];
                sorted[j]      = sorted[j + 1];
                sorted[j + 1]  = temp;
            }
        }
    }

    printf("\n%-4s %-25s %-15s %10s\n", "No.", "Description", "Category",
           "Amount");
    printf("----------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-4d %-25s %-15s %10.2f\n", i + 1, sorted[i].description,
               categoryNames[sorted[i].category], sorted[i].amount);
    }
}

/* ---------- PART 7: calculations ---------- */

double calculateTotal(const Expense expenses[], int count)
{
    double total = 0;
    for (int i = 0; i < count; i++) {
        total += expenses[i].amount;
    }
    return total;
}

void calculateCategoryTotals(const Expense expenses[], int count,
                             double totals[])
{
    for (int i = 0; i < NUM_CATEGORIES; i++) {   /* reset first */
        totals[i] = 0;
    }
    for (int i = 0; i < count; i++) {
        totals[expenses[i].category] += expenses[i].amount;
    }
}

/* Returns index of the biggest category, or -1 if nothing was spent. */
int findHighestCategory(const double totals[])
{
    int maxIndex = 0;
    for (int i = 1; i < NUM_CATEGORIES; i++) {
        if (totals[i] > totals[maxIndex]) {
            maxIndex = i;
        }
    }
    if (totals[maxIndex] <= 0) {
        return -1;
    }
    return maxIndex;
}

/* ---------- PART 8: budget status and summary ---------- */

void displayBudgetStatus(double budget, double total)
{
    if (total > budget) {
        printf("STATUS: WARNING! Budget exceeded by %.2f!\n", total - budget);
    } else if (total >= WARN_RATIO * budget) {
        printf("STATUS: Caution - you have used %.1f%% of your budget.\n",
               total / budget * 100);
    } else {
        printf("STATUS: Within budget (%.1f%% used).\n",
               total / budget * 100);
    }
}

void displaySummary(const Expense expenses[], int count, double budget)
{
    double total = calculateTotal(expenses, count);
    double categoryTotals[NUM_CATEGORIES];
    calculateCategoryTotals(expenses, count, categoryTotals);

    printf("\n========== EXPENSE SUMMARY ==========\n");
    printf("Expenses recorded : %d\n", count);
    printf("Monthly budget    : %10.2f\n", budget);
    printf("Total spent       : %10.2f\n", total);
    printf("Remaining budget  : %10.2f\n", budget - total);

    printf("\n--- Category-wise totals ---\n");
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        printf("%-15s %10.2f\n", categoryNames[i], categoryTotals[i]);
    }

    int top = findHighestCategory(categoryTotals);
    if (top == -1) {
        printf("\nHighest spending  : none yet\n");
    } else {
        printf("\nHighest spending  : %s (%.2f)\n", categoryNames[top],
               categoryTotals[top]);
    }

    printf("\n");
    displayBudgetStatus(budget, total);
    printf("=====================================\n");
}

/* ---------- PART 9: file handling ---------- */

/* File format:
 *   line 1: budget
 *   line 2+: category,amount,description
 */
int saveData(const char *filename, const Expense expenses[],
             int count, double budget)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Could not open %s for writing.\n", filename);
        return 0;
    }

    fprintf(fp, "%.2f\n", budget);
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d,%.2f,%s\n", (int)expenses[i].category,
                expenses[i].amount, expenses[i].description);
    }

    fclose(fp);
    return 1;
}

int loadData(const char *filename, Expense expenses[],
             int *count, double *budget)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return 0;                            /* first run: no file yet */
    }

    char line[128];
    if (fgets(line, sizeof line, fp) == NULL ||
        sscanf(line, "%lf", budget) != 1 || *budget <= 0) {
        fclose(fp);
        return 0;                            /* corrupt or empty file */
    }

    *count = 0;
    while (*count < MAX_EXPENSES && fgets(line, sizeof line, fp) != NULL) {
        int    cat;
        double amt;
        char   desc[DESC_LEN];

        if (sscanf(line, "%d,%lf,%49[^\n]", &cat, &amt, desc) == 3 &&
            cat >= 0 && cat < NUM_CATEGORIES && amt > 0) {
            expenses[*count].category = (Category)cat;
            expenses[*count].amount   = amt;
            strcpy(expenses[*count].description, desc);
            (*count)++;
        }
    }

    fclose(fp);
    return 1;
}

/* ---------- PART 10: main ---------- */

int main(void)
{
    Expense expenses[MAX_EXPENSES];
    int     count  = 0;
    double  budget = 0;

    printf("Welcome to the Personal Expense Tracker!\n");

    if (loadData(DATA_FILE, expenses, &count, &budget)) {
        printf("Loaded %d saved expense(s). Budget: %.2f\n", count, budget);
    } else {
        budget = readDouble("Enter your monthly budget: ", 0);
    }

    int choice;
    do {
        showMenu();
        choice = readInt("Enter choice: ", 1, 6);

        switch (choice) {
            case 1:
                addExpense(expenses, &count);
                break;
            case 2:
                listExpensesSorted(expenses, count);
                break;
            case 3:
                displaySummary(expenses, count, budget);
                break;
            case 4:
                budget = readDouble("Enter new monthly budget: ", 0);
                printf("Budget updated to %.2f\n", budget);
                break;
            case 5:
                if (saveData(DATA_FILE, expenses, count, budget)) {
                    printf("Data saved.\n");
                }
                break;
            case 6:
                if (saveData(DATA_FILE, expenses, count, budget)) {
                    printf("Data saved. Goodbye!\n");
                }
                break;
        }
    } while (choice != 6);

    return 0;
}
