#include <iostream>
#include <string>
#include <unordered_map>

// Function prototypes
void printIntroMenu();
void printMainMenu();
void start();
void login();
void createAccount();
void depositMoney();
void withdrawMoney();
void requestBalance();

// Global variable to store menu selection
char menuInput;
std::unordered_map<std::string, std::string> userAccounts; // Stores user id and password
std::unordered_map<std::string, double> accountBalances; // Stores user id and balance
std::string currentUser; // Tracks logged-in user

int main() {
    std::cout << "Hi! Welcome to Mr. Appleton's ATM Machine!" << std::endl;
    start();
    return 0;
}

// Displays the introductory menu
void printIntroMenu() {
    std::cout << "\nPlease select an option from the menu below:\n";
    std::cout << "l -> Login\nc -> Create New Account\nq -> Quit\n> ";
}

// Displays the main account menu after login
void printMainMenu() {
    std::cout << "\nd -> Deposit Money\nw -> Withdraw Money\nr -> Request Balance\nq -> Quit\n> ";
}

// Handles the main loop for initial login, account creation, or quit
void start() {
    while (true) {
        printIntroMenu();
        std::cin >> menuInput;

        switch (menuInput) {
            case 'l': login(); break;
            case 'c': createAccount(); break;
            case 'q': exit(0);
            default: std::cout << "Invalid option. Try again.\n"; break;
        }
    }
}

// Creates a new account
void createAccount() {
    std::string userId, password;
    std::cout << "Please enter your user id: ";
    std::cin >> userId;
    std::cout << "Please enter your password: ";
    std::cin >> password;

    // Checks if user id already exists
    if (userAccounts.find(userId) == userAccounts.end()) {
        userAccounts[userId] = password;
        accountBalances[userId] = 0.0; // Initialize balance to zero
        std::cout << "Thank You! Your account has been created!\n";
    } else {
        std::cout << "User ID already exists. Please choose a different ID.\n";
    }
}

// Handles user login
void login() {
    std::string userId, password;
    std::cout << "Please enter your user id: ";
    std::cin >> userId;
    std::cout << "Please enter your password: ";
    std::cin >> password;

    // Verifies user account information
    if (userAccounts.find(userId) != userAccounts.end() && userAccounts[userId] == password) {
        std::cout << "Access Granted!\n";
        currentUser = userId;

        // Loop for account management
        while (true) {
            printMainMenu();
            std::cin >> menuInput;

            switch (menuInput) {
                case 'd': depositMoney(); break;
                case 'w': withdrawMoney(); break;
                case 'r': requestBalance(); break;
                case 'q': std::cout << "Thanks for stopping by!\n"; return;
                default: std::cout << "Invalid option. Try again.\n"; break;
            }
        }
    } else {
        std::cout << "******** LOGIN FAILED! ********\n";
    }
}

// Deposits money to the account
void depositMoney() {
    double amount;
    std::cout << "Amount of deposit: $";
    std::cin >> amount;

    if (amount > 0) {
        accountBalances[currentUser] += amount;
        std::cout << "Deposit successful! New balance: $" << accountBalances[currentUser] << "\n";
    } else {
        std::cout << "Deposit amount must be positive.\n";
    }
}

// Withdraws money from the account
void withdrawMoney() {
    double amount;
    std::cout << "Amount of withdrawal: $";
    std::cin >> amount;

    if (amount > 0 && amount <= accountBalances[currentUser]) {
        accountBalances[currentUser] -= amount;
        std::cout << "Withdrawal successful! New balance: $" << accountBalances[currentUser] << "\n";
    } else {
        std::cout << "Insufficient balance or invalid amount.\n";
    }
}

// Checks account balance
void requestBalance() {
    std::cout << "Your balance is $" << accountBalances[currentUser] << "\n";
}