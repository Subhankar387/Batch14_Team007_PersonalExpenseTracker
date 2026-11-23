# Personal Expense Tracker

## Problem Statement
Build a simple expense tracker to help a student manage a monthly budget.

## Team Details
- Team Number: 7
- Batch: 14
- **Members:**
  1. Subhankar Nag
  2. Saayuj Tiwari
  3. Pranali Mewar 

## Objectives
- Record expenses with a description, amount, and category.
- Calculate total spending, remaining budget, and category-wise totals.
- Store and reload data using file handling.
- Validate all user input so the program never crashes on bad entries.

## Features
- Set and change the monthly budget
- Add an expense (Food, Travel, Books, Entertainment)
- View all expenses sorted from highest to lowest amount
- Summary: total spent, remaining budget, category-wise totals, highest spending category
- Budget status: within budget, caution (90% or more used), or exceeded
- Save data to `expenses.txt` and auto-load it on the next run
- Input validation for numbers, menu choices, and empty descriptions

## Algorithm
1. Start
2. Load saved data from `expenses.txt`. If there is no file, ask the user for a monthly budget.
3. Display the menu and read a valid choice (1-6).
4. If **Add**: read description, amount (> 0) and category, then store the expense in the array.
5. If **View**: copy the array, bubble-sort it by amount (descending), and print it.
6. If **Summary**: compute total, category totals, highest category, and budget status.
7. If **Change budget**: read the new budget (> 0).
8. If **Save**: write the budget and all expenses to the file.
9. If **Save and Exit**: save, then stop. Otherwise go back to step 3.
10. End

## Flowchart
```mermaid
flowchart TD
    A([Start]) --> B{expenses.txt found?}
    B -->|Yes| C[Load budget and expenses]
    B -->|No| D[/Read monthly budget/]
    C --> E[Display menu]
    D --> E
    E --> F[/Read choice 1-6/]
    F --> G{Choice?}
    G -->|1| H[Add expense]
    G -->|2| I[Sort copy and list expenses]
    G -->|3| J[Show summary and budget status]
    G -->|4| K[Change budget]
    G -->|5| L[Save data]
    G -->|6| M[Save data]
    H --> E
    I --> E
    J --> E
    K --> E
    L --> E
    M --> N([End])```## Sample Test Cases

| # | Scenario | Input | Expected Output | Actual Output |
|---|----------|-------|-----------------|---------------|
| 1 | First run, set budget | Budget: `1000` | Menu is displayed | Menu is displayed |
| 2 | Invalid budget | Budget: `-50`, then `abc`, then `1000` | "Invalid input. Enter a number greater than 0.00." shown twice, then accepted | Same as expected |
| 3 | Add valid expense | Choice `1`, Desc: `Lunch`, Amount: `200`, Category: `1` | "Expense added." | Same as expected |
| 4 | Invalid amount | Amount: `0` | "Invalid input. Enter a number greater than 0.00." | Same as expected |
| 5 | Invalid category | Category: `7` | "Invalid input. Enter a whole number from 1 to 4." | Same as expected |
| 6 | Invalid menu choice | Choice: `9` | "Invalid input. Enter a whole number from 1 to 6." | Same as expected |
| 7 | View with no expenses | Choice `2` | "No expenses recorded yet." | Same as expected |
| 8 | Sorted view | Add Lunch 200, Bus 150, Novel 500, then choice `2` | Order: Novel (500.00), Lunch (200.00), Bus (150.00) | Same as expected |
| 9 | Summary within budget | Budget 1000, Lunch 200 (Food), Bus 150 (Travel), choice `3` | Total 350.00, Remaining 650.00, Highest: Food (200.00), "Within budget (35.0% used)." | Same as expected |
| 10 | Caution warning | Budget 1000, total spent 950 | "Caution - you have used 95.0% of your budget." | Same as expected |
| 11 | Budget exceeded | Budget 500, total spent 600 | "WARNING! Budget exceeded by 100.00!" | Same as expected |
| 12 | Save and reload | Add expenses, choice `6`, run again | "Loaded N saved expense(s). Budget: 1000.00" | Same as expected |

## Sample Test Cases

| # | Scenario | Input | Expected Output | Actual Output |
|---|----------|-------|-----------------|---------------|
| 1 | First run, set budget | Budget: `1000` | Menu is displayed | Menu is displayed |
| 2 | Invalid budget | Budget: `-50`, then `abc`, then `1000` | "Invalid input. Enter a number greater than 0.00." shown twice, then accepted | Same as expected |
| 3 | Add valid expense | Choice `1`, Desc: `Lunch`, Amount: `200`, Category: `1` | "Expense added." | Same as expected |
| 4 | Invalid amount | Amount: `0` | "Invalid input. Enter a number greater than 0.00." | Same as expected |
| 5 | Invalid category | Category: `7` | "Invalid input. Enter a whole number from 1 to 4." | Same as expected |
| 6 | Invalid menu choice | Choice: `9` | "Invalid input. Enter a whole number from 1 to 6." | Same as expected |
| 7 | View with no expenses | Choice `2` | "No expenses recorded yet." | Same as expected |
| 8 | Sorted view | Add Lunch 200, Bus 150, Novel 500, then choice `2` | Order: Novel (500.00), Lunch (200.00), Bus (150.00) | Same as expected |
| 9 | Summary within budget | Budget 1000, Lunch 200 (Food), Bus 150 (Travel), choice `3` | Total 350.00, Remaining 650.00, Highest: Food (200.00), "Within budget (35.0% used)." | Same as expected |
| 10 | Caution warning | Budget 1000, total spent 950 | "Caution - you have used 95.0% of your budget." | Same as expected |
| 11 | Budget exceeded | Budget 500, total spent 600 | "WARNING! Budget exceeded by 100.00!" | Same as expected |
| 12 | Save and reload | Add expenses, choice `6`, run again | "Loaded N saved expense(s). Budget: 1000.00" | Same as expected |
