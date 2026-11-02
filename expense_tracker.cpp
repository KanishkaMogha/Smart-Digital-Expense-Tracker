#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

struct Expense
{
    string date;
    string category;
    string description;
    double amount;
};

Expense e[500];
int countExpense = 0;
double budget = 0;

// Save expenses in file
void saveExpenses()
{
    ofstream file("expenses.txt");

    for(int i = 0; i < countExpense; i++)
    {
        file << e[i].date << "|"
             << e[i].category << "|"
             << e[i].description << "|"
             << e[i].amount << endl;
    }

    file.close();
}

// Load expenses from file
void loadExpenses()
{
    ifstream file("expenses.txt");
    countExpense = 0;

    while(getline(file, e[countExpense].date, '|'))
    {
        getline(file, e[countExpense].category, '|');
        getline(file, e[countExpense].description, '|');

        string amount;
        getline(file, amount);

        e[countExpense].amount = stod(amount);
        countExpense++;

        if(countExpense >= 500)
            break;
    }

    file.close();
}

// Add daily expense
void addExpense()
{
    if(countExpense >= 500)
    {
        cout << "Expense limit reached!\n";
        return;
    }

    cout << "Enter Date (YYYY-MM-DD): ";
    getline(cin, e[countExpense].date);

    cout << "Enter Category: ";
    getline(cin, e[countExpense].category);

    cout << "Enter Description: ";
    getline(cin, e[countExpense].description);

    cout << "Enter Amount: ";
    cin >> e[countExpense].amount;
    cin.ignore();

    countExpense++;

    saveExpenses();

    cout << "Expense added successfully!\n";
}

// View expense history
void viewExpenses()
{
    cout << "\n--- Expense History ---\n";

    for(int i = 0; i < countExpense; i++)
    {
        cout << "\nDate: " << e[i].date;
        cout << "\nCategory: " << e[i].category;
        cout << "\nDescription: " << e[i].description;
        cout << "\nAmount: Rs. " << e[i].amount << endl;
    }
}

// Category-wise expense
void categoryExpense()
{
    string cat;
    double total = 0;

    cout << "Enter Category: ";
    getline(cin, cat);

    for(int i = 0; i < countExpense; i++)
    {
        if(e[i].category == cat)
            total += e[i].amount;
    }

    cout << "Total " << cat << " Expense: Rs. "
         << total << endl;
}

// Monthly expense report
void monthlyReport()
{
    string month;
    double total = 0;

    cout << "Enter Month (YYYY-MM): ";
    getline(cin, month);

    for(int i = 0; i < countExpense; i++)
    {
        if(e[i].date.substr(0, 7) == month)
            total += e[i].amount;
    }

    cout << "Monthly Expense: Rs. "
         << total << endl;
}

// Set monthly budget
void setBudget()
{
    cout << "Enter Monthly Budget: Rs. ";
    cin >> budget;
    cin.ignore();

    ofstream file("budget.txt");
    file << budget;
    file.close();

    cout << "Budget saved successfully!\n";
}

// Budget warning
void budgetWarning()
{
    double total = 0;

    for(int i = 0; i < countExpense; i++)
        total += e[i].amount;

    cout << "Total Expense: Rs. " << total << endl;
    cout << "Monthly Budget: Rs. " << budget << endl;

    if(budget > 0 && total >= budget)
        cout << "Warning! Budget exceeded!\n";
    else
        cout << "You are within your budget.\n";
}

// Predict monthly expense
void predictExpense()
{
    int days;
    double total = 0;

    cout << "Enter number of days passed: ";
    cin >> days;
    cin.ignore();

    for(int i = 0; i < countExpense; i++)
        total += e[i].amount;

    if(days <= 0)
    {
        cout << "Invalid number of days!\n";
        return;
    }

    double prediction = (total / days) * 30;

    cout << "Predicted Monthly Expense: Rs. "
         << prediction << endl;

    if(budget > 0 && prediction > budget)
        cout << "Alert! You may exceed your budget.\n";
    else
        cout << "Your predicted expense is within budget.\n";
}

// Search expense
void searchExpense()
{
    string cat;
    bool found = false;

    cout << "Enter category to search: ";
    getline(cin, cat);

    for(int i = 0; i < countExpense; i++)
    {
        if(e[i].category == cat)
        {
            cout << e[i].date << " "
                 << e[i].category << " Rs. "
                 << e[i].amount << endl;

            found = true;
        }
    }

    if(!found)
        cout << "Expense not found!\n";
}

// Delete expense
void deleteExpense()
{
    int pos;

    viewExpenses();

    cout << "Enter expense number to delete: ";
    cin >> pos;
    cin.ignore();

    if(pos < 1 || pos > countExpense)
    {
        cout << "Invalid expense number!\n";
        return;
    }

    for(int i = pos - 1; i < countExpense - 1; i++)
        e[i] = e[i + 1];

    countExpense--;

    saveExpenses();

    cout << "Expense deleted successfully!\n";
}

// Sort expenses
void sortExpenses()
{
    sort(e, e + countExpense,
         [](Expense a, Expense b)
         {
             return a.amount > b.amount;
         });

    saveExpenses();

    cout << "Expenses sorted by amount (highest first).\n";
    viewExpenses();
}

// Main function
int main()
{
    ifstream budgetFile("budget.txt");

    if(budgetFile)
        budgetFile >> budget;

    budgetFile.close();

    loadExpenses();

    int choice;

    do
    {
        cout << "\n===== SMART DIGITAL EXPENSE TRACKER =====\n";
        cout << "1. Add Daily Expense\n";
        cout << "2. View Expense History\n";
        cout << "3. Category-wise Expense\n";
        cout << "4. Monthly Expense Report\n";
        cout << "5. Set Monthly Budget\n";
        cout << "6. Budget Warning\n";
        cout << "7. Expense Prediction\n";
        cout << "8. Search Expense\n";
        cout << "9. Delete Expense\n";
        cout << "10. Sort Expenses\n";
        cout << "0. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;
        cin.ignore();

        switch(choice)
        {
            case 1: addExpense(); break;
            case 2: viewExpenses(); break;
            case 3: categoryExpense(); break;
            case 4: monthlyReport(); break;
            case 5: setBudget(); break;
            case 6: budgetWarning(); break;
            case 7: predictExpense(); break;
            case 8: searchExpense(); break;
            case 9: deleteExpense(); break;
            case 10: sortExpenses(); break;
            case 0: cout << "Thank you for using the tracker!\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while(choice != 0);

    return 0;
}
