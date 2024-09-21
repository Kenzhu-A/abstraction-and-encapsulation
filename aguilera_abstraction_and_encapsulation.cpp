#include <iostream>
#include <limits>  

using namespace std;

class BankAccount {
protected:
    double balance;

public:
    BankAccount(double initialBalance) : balance(initialBalance) {}

    void deposit(double amount) {

        if (amount > 0) {

            balance += amount;
            cout << "Deposit successful. New balance: " << balance << endl;
        } else {
            cout << "Invalid amount. Please enter a positive value." << endl;
        }
    }

    virtual void withdraw(double amount) = 0;

    void checkBalance() const {
        cout << "Current balance: " << balance << endl;
    }
};

class SavingsAccount : public BankAccount {
private:
    const double MIN_BALANCE = 1000;

public:
    SavingsAccount(double initialBalance) : BankAccount(initialBalance) {}

    void withdraw(double amount) override {
        if (amount <= 0) {
            cout << "Invalid amount. Please enter a positive value." << endl;
        } else if (balance - amount < MIN_BALANCE) {
            cout << "Withdrawal failed: Minimum balance of 1000 must be maintained." << endl;
        } else if (amount > balance) {
            cout << "Withdrawal failed: Insufficient funds." << endl;
        } else {
            balance -= amount;
            cout << "Withdrawal successful. New balance: " << balance << endl;
        }
    }
};

class CurrentAccount : public BankAccount {
public:
    CurrentAccount(double initialBalance) : BankAccount(initialBalance) {}

    void withdraw(double amount) override {
        if (amount <= 0) {
            cout << "Invalid amount. Please enter a positive value." << endl;
        } else if (amount > balance) {
            cout << "Withdrawal failed: Insufficient funds." << endl;
        } else {
            balance -= amount;
            cout << "Withdrawal successful. New balance: " << balance << endl;
        }
    }
};


bool getInput(double &input) {
    cin >> input;
    if (cin.fail()) {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid number: ";
        return false; 
    }
    return true; 
}

bool getInput(int &input) {
    cin >> input;
    if (cin.fail()) { 
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "Invalid input. Please enter a valid number: ";
        return false; 
    }
    return true; 
}

void mainMenu() {
    cout << "\nMain Menu\n";
    cout << "1 - Savings Account\n";
    cout << "2 - Current Account\n";
    cout << "3 - Exit\n";
    cout << "Select an option: ";
}

void subMenu() {
    cout << "\nSub Menu\n";
    cout << "1 - Deposit\n";
    cout << "2 - Withdraw\n";
    cout << "3 - Check Balance\n";
    cout << "4 - Back\n";
    cout << "Select an option: ";
}

int main() {
    int mainChoice = 0;
    double amount;
    BankAccount* account = nullptr;
    double initialBalance;


    while (mainChoice != 3) {
        mainMenu();

        
        while (!getInput(mainChoice) || (mainChoice < 1 || mainChoice > 3)) {
            cout << "Invalid option! Try again." << endl;
        }

        switch (mainChoice) {
            case 1: 

                do {
                    cout << "Enter initial balance for Savings Account (minimum 1000): ";
                } while (!getInput(initialBalance) || initialBalance < 1000);

                account = new SavingsAccount(initialBalance);
                break;

            case 2: 

                do {
                    cout << "Enter initial balance for Current Account: ";
                } while (!getInput(initialBalance));

                account = new CurrentAccount(initialBalance);
                break;

            case 3:
                cout << "Exiting the system..." << endl;
                break;

            default:
                cout << "Invalid option! Try again." << endl;
        }

    
        if (mainChoice == 1 || mainChoice == 2) {
            int subChoice = 0;
            do {
                subMenu();

       
                while (!getInput(subChoice) || (subChoice < 1 || subChoice > 4)) {
                    cout << "Invalid option! Try again." << endl;
                }

                switch (subChoice) {
                    case 1: 
                        cout << "Enter amount to deposit: ";
                        while (!getInput(amount) || amount <= 0) {
                            cout << "Invalid amount. Please enter a positive value." << endl;
                        }
                        account->deposit(amount);
                        break;

                    case 2: 

                        cout << "Enter amount to withdraw: ";
                        while (!getInput(amount) || amount <= 0) {
                            cout << "Invalid amount. Please enter a positive value." << endl;
                        }
                        account->withdraw(amount);
                        break;

                    case 3:
                        account->checkBalance();
                        break;

                    case 4: 
                        delete account; 
                        account = nullptr;
                        break;

                    default:
                        cout << "Invalid option! Try again." << endl;
                }

            } while (subChoice != 4);
        }
    }

    return 0;
}
