#include <iostream>
#include <vector>
#include <exception>
using namespace std;

/* =======================
   🔹 Custom Exceptions
   ======================= */

class InsufficientBalanceException : public exception {
public:
    const char* what() const noexcept {
        return "Insufficient Balance!";
    }
};

class InvalidAmountException : public exception {
public:
    const char* what() const noexcept {
        return "Invalid Amount! Must be > 0";
    }
};

class AccountNotFoundException : public exception {
public:
    const char* what() const noexcept {
        return "Account Not Found!";
    }
};


/* =======================
   🔹 Base Class (OOP)
   ======================= */

class BankAccount {
protected:
    int accountNumber;
    string name;
    double balance;

public:
    BankAccount(int accNo, string name, double balance) {
        this->accountNumber = accNo;
        this->name = name;
        this->balance = balance;
    }

    virtual void deposit(double amount) {
        if (amount <= 0)
            throw InvalidAmountException();

        balance += amount;
        cout << "✅ Deposited: " << amount << endl;
    }

    virtual void withdraw(double amount) {
        if (amount <= 0)
            throw InvalidAmountException();

        if (amount > balance)
            throw InsufficientBalanceException();

        balance -= amount;
        cout << "✅ Withdrawn: " << amount << endl;
    }

    virtual void display() {
        cout << "\n--- Account Info ---\n";
        cout << "Account No: " << accountNumber << endl;
        cout << "Name: " << name << endl;
        cout << "Balance: " << balance << endl;
    }

    int getAccountNumber() {
        return accountNumber;
    }

    virtual ~BankAccount() {}
};


/* =======================
   🔹 Derived Class
   ======================= */

class PremiumAccount : public BankAccount {
public:
    PremiumAccount(int accNo, string name, double balance)
        : BankAccount(accNo, name, balance) {}

    void withdraw(double amount) override {
        cout << "[Premium Account] Fast withdrawal\n";
        BankAccount::withdraw(amount);
    }
};


/* =======================
   🔹 Bank System Manager
   ======================= */

class BankSystem {
private:
    vector<BankAccount*> accounts;

public:

    // Create Account
    void createAccount() {
        int accNo;
        string name;
        double balance;
        int type;

        cout << "Enter Account Number: ";
        cin >> accNo;

        cout << "Enter Name: ";
        cin >> name;

        cout << "Enter Initial Balance: ";
        cin >> balance;

        cout << "1. Normal Account\n2. Premium Account\nChoose type: ";
        cin >> type;

        if (type == 1)
            accounts.push_back(new BankAccount(accNo, name, balance));
        else
            accounts.push_back(new PremiumAccount(accNo, name, balance));

        cout << "✅ Account Created Successfully!\n";
    }

    // Find Account
    BankAccount* findAccount(int accNo) {
        for (auto acc : accounts) {
            if (acc->getAccountNumber() == accNo)
                return acc;
        }
        throw AccountNotFoundException();
    }

    // Deposit
    void deposit() {
        int accNo;
        double amount;

        cout << "Enter Account Number: ";
        cin >> accNo;

        cout << "Enter Amount: ";
        cin >> amount;

        try {
            BankAccount* acc = findAccount(accNo);
            acc->deposit(amount);
        }
        catch (exception &e) {
            cout << "❌ Error: " << e.what() << endl;
        }
    }

    // Withdraw
    void withdraw() {
        int accNo;
        double amount;

        cout << "Enter Account Number: ";
        cin >> accNo;

        cout << "Enter Amount: ";
        cin >> amount;

        try {
            BankAccount* acc = findAccount(accNo);
            acc->withdraw(amount);
        }
        catch (exception &e) {
            cout << "❌ Error: " << e.what() << endl;
        }
    }

    // Display Account
    void display() {
        int accNo;
        cout << "Enter Account Number: ";
        cin >> accNo;

        try {
            BankAccount* acc = findAccount(accNo);
            acc->display();
        }
        catch (exception &e) {
            cout << "❌ Error: " << e.what() << endl;
        }
    }

    // Destructor (free memory)
    ~BankSystem() {
        for (auto acc : accounts)
            delete acc;
    }
};


/* =======================
   🔹 Main Menu (CLI)
   ======================= */

int main() {
    BankSystem bank;
    int choice;

    do {
        cout << "\n====== BANK MENU ======\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Display Account\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bank.createAccount();
                break;
            case 2:
                bank.deposit();
                break;
            case 3:
                bank.withdraw();
                break;
            case 4:
                bank.display();
                break;
            case 5:
                cout << "👋 Exiting...\n";
                break;
            default:
                cout << "❌ Invalid Choice!\n";
        }

    } while (choice != 5);

    return 0;
}