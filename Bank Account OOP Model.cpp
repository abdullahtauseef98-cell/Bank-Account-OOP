#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Account
{
protected:
    int accountNumber;
    string holderName;
    double balance;

public:
    Account(int accNo, string name, double bal)
    {
        accountNumber = accNo;
        holderName = name;
        balance = bal;
    }

    virtual void deposit(double amount)
    {
        balance += amount;
        cout << "Deposit Successful.\n";
        logTransaction("Deposit", amount);
    }

    virtual void withdraw(double amount)
    {
        try
        {
            if (amount > balance)
            {
                throw "Insufficient Balance!";
            }

            balance -= amount;
            cout << "Withdrawal Successful.\n";
            logTransaction("Withdraw", amount);
        }
        catch (const char *msg)
        {
            cout << msg << endl;
        }
    }

    virtual void display()
    {
        cout << "\nAccount Number: " << accountNumber << endl;
        cout << "Account Holder: " << holderName << endl;
        cout << "Balance: " << balance << endl;
    }

    void logTransaction(string type, double amount)
    {
        ofstream file("transactions.txt", ios::app);

        file << type << " | "
             << "Account: " << accountNumber
             << " | Amount: " << amount
             << " | Balance: " << balance << endl;

        file.close();
    }

    virtual ~Account()
    {
    }
};

class SavingsAccount : public Account
{
public:
    SavingsAccount(int accNo, string name, double bal)
        : Account(accNo, name, bal)
    {
    }

    void display()
    {
        cout << "\n----- Savings Account -----\n";
        Account::display();
    }
};

class CheckingAccount : public Account
{
public:
    CheckingAccount(int accNo, string name, double bal)
        : Account(accNo, name, bal)
    {
    }

    void display()
    {
        cout << "\n----- Checking Account -----\n";
        Account::display();
    }
};

int main()
{
    int choice;
    int type;
    int accNo;
    string name;
    double balance;

    Account *account = NULL;

    cout << "Choose Account Type\n";
    cout << "1. Savings Account\n";
    cout << "2. Checking Account\n";
    cout << "Enter Choice: ";
    cin >> type;

    cout << "Enter Account Number: ";
    cin >> accNo;

    cin.ignore();

    cout << "Enter Holder Name: ";
    getline(cin, name);

    cout << "Enter Initial Balance: ";
    cin >> balance;

    if (type == 1)
    {
        account = new SavingsAccount(accNo, name, balance);
    }
    else
    {
        account = new CheckingAccount(accNo, name, balance);
    }

    do
    {
        cout << "\n===== Bank Account System =====\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Display Account\n";
        cout << "4. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        double amount;

        switch (choice)
        {
        case 1:
            cout << "Enter Amount: ";
            cin >> amount;
            account->deposit(amount);
            break;

        case 2:
            cout << "Enter Amount: ";
            cin >> amount;
            account->withdraw(amount);
            break;

        case 3:
            account->display();
            break;

        case 4:
            cout << "Thank You!\n";
            break;

        default:
            cout << "Invalid Choice.\n";
        }

    } while (choice != 4);

    delete account;

    return 0;
}
