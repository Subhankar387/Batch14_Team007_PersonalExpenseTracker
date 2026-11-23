# Personal Expense Tracker

## Problem Statement
Build a simple expense tracker to help a student manage a monthly budget.

## Team Details
- Team Number: 007
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
