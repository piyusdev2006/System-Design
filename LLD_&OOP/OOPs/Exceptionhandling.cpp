#include <iostream>
#include <exception>
using namespace std;

/* =======================
   🔹 Custom Exceptions
   ======================= */

// Exception for insufficient balance
class InsufficientBalanceException : public exception {
public:
    const char* what() const noexcept {
        return "Insufficient Balance!";
    }
};

// Exception for invalid amount (negative or zero)
class InvalidAmountException : public exception {
public:
    const char* what() const noexcept {
        return "Invalid Amount! Amount must be > 0";
    }
};


/* =======================
   🔹 Bank Account Class
   ======================= */

class BankAccount {
private:
    string name;      // Customer name
    double balance;   // Account balance

public:
    // Constructor to initialize account
    BankAccount(string name, double balance) {
        this->name = name;
        this->balance = balance;
    }

    // Deposit function
    void deposit(double amount) {
        // Validate amount
        if (amount <= 0) {
            throw InvalidAmountException();
        }

        balance += amount;
        cout << "Deposited: " << amount << endl;
    }

    // Withdraw function
    void withdraw(double amount) {
        // Check invalid amount
        if (amount <= 0) {
            throw InvalidAmountException();
        }

        // Check insufficient balance
        if (amount > balance) {
            throw InsufficientBalanceException();
        }

        balance -= amount;
        cout << "Withdrawn: " << amount << endl;
    }

    // Display account details
    void display() {
        cout << "\n--- Account Details ---\n";
        cout << "Customer: " << name << endl;
        cout << "Balance: " << balance << endl;
    }
};


/* =======================
   🔹 Derived Class (Inheritance)
   ======================= */

class PremiumAccount : public BankAccount {
public:
    // Constructor calling base class constructor
    PremiumAccount(string name, double balance)
        : BankAccount(name, balance) {}

    // Overriding withdraw method
    void withdraw(double amount) {
        cout << "[Premium Account] Processing withdrawal...\n";
        
        // Call base class withdraw
        BankAccount::withdraw(amount);
    }
};


/* =======================
   🔹 Main Function
   ======================= */

int main() {

    // Create a Premium Account object
    PremiumAccount acc("Naveen", 5000);

    try {
        // Valid deposit
        acc.deposit(2000);

        // Invalid withdraw (will throw exception)
        acc.withdraw(8000);

        // Another invalid case (uncomment to test)
        // acc.deposit(-100);

    }
    catch (InvalidAmountException &e) {
        // Handle invalid amount error
        cout << "Error: " << e.what() << endl;
    }
    catch (InsufficientBalanceException &e) {
        // Handle insufficient balance
        cout << "Error: " << e.what() << endl;
    }
    catch (exception &e) {
        // General exception handler
        cout << "General Error: " << e.what() << endl;
    }

    // Display final account state
    acc.display();

    return 0;
}