#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Define account structure
typedef struct {
    int account_number;
    char pin[5];
    double balance;
} Account;

// Function prototypes
void displayWelcomeMessage();
bool verifyPin(Account *accounts, int num_accounts, Account **logged_in_account);
void displayMenu();
void checkBalance(Account *account);
void deposit(Account *account);
void withdraw(Account *account);

int main() {
    Account accounts[] = {
        {12345678, "1234", 1000.00},
        {87654321, "4321", 500.00},
        {11223344, "5678", 750.00}
    };

    int num_accounts = sizeof(accounts) / sizeof(Account);
    Account *logged_in_account = NULL;

    displayWelcomeMessage();

    if (!verifyPin(accounts, num_accounts, &logged_in_account)) {
        printf("Too many incorrect attempts. Exiting.\n");
        return 1;
    }

    int choice;
    bool done = false;

    while (!done) {
        displayMenu();
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                checkBalance(logged_in_account);
                break;
            case 2:
                deposit(logged_in_account);
                break;
            case 3:
                withdraw(logged_in_account);
                break;
            case 4:
                printf("Thank you for using the ATM. Goodbye!\n");
                done = true;
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }

        printf("\n");
    }

    return 0;
}

void displayWelcomeMessage() {
    printf("================================\n");
    printf("|    Welcome to the ATM!       |\n");
    printf("================================\n\n");
}

bool verifyPin(Account *accounts, int num_accounts, Account **logged_in_account) {
    int account_number;
    char enteredPin[5];
    int attempts = 0;

    printf("Please enter your account number: ");
    scanf("%d", &account_number);

    for (int i = 0; i < num_accounts; i++) {
        if (accounts[i].account_number == account_number) {
            while (attempts < 3) {
                printf("Please enter your PIN: ");
                scanf("%4s", enteredPin);

                if (strcmp(enteredPin, accounts[i].pin) == 0) {
                    printf("PIN verified successfully.\n\n");
                    *logged_in_account = &accounts[i];
                    return true;
                } else {
                    printf("Incorrect PIN. Please try again.\n");
                    attempts++;
                }
            }
            return false;
        }
    }

    printf("Account number not found.\n");
    return false;
}

void displayMenu() {
    printf("1. Check Balance\n");
    printf("2. Deposit Money\n");
    printf("3. Withdraw Money\n");
    printf("4. Exit\n");
}

void checkBalance(Account *account) {
    printf("Your current balance is: $%.2f\n", account->balance);
}

void deposit(Account *account) {
    double amount;
    printf("Enter amount to deposit: $");
    scanf("%lf", &amount);

    if (amount > 0) {
        account->balance += amount;
        printf("Deposit successful. Your new balance is: $%.2f\n", account->balance);
    } else {
        printf("Invalid amount. Deposit failed.\n");
    }
}

void withdraw(Account *account) {
    double amount;
    printf("Enter amount to withdraw: $");
    scanf("%lf", &amount);

    if (amount > 0 && amount <= account->balance) {
        account->balance -= amount;
        printf("Withdrawal successful. Your new balance is: $%.2f\n", account->balance);
    } else {
        printf("Invalid amount or insufficient balance. Withdrawal failed.\n");
    }
}
