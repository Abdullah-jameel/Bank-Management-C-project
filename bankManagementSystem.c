#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a bank account
struct BankAccount {
    int accountNumber;
    char holderName[50];
    float balance;
};

// Function prototypes
void createAccount(struct BankAccount *accounts, int *numAccounts);
void deposit(struct BankAccount *accounts, int numAccounts);
void withdraw(struct BankAccount *accounts, int numAccounts);
void checkBalance(struct BankAccount *accounts, int numAccounts);
void displayAccountDetails(struct BankAccount *accounts, int numAccounts);
void saveAccountsToFile(struct BankAccount *accounts, int numAccounts, const char *filename);
void loadAccountsFromFile(struct BankAccount *accounts, int *numAccounts, const char *filename);

int main() {
    struct BankAccount accounts[100]; // Assuming a maximum of 100 accounts
    int numAccounts = 0;
    int choice;
    
    // Load accounts from file at the beginning
    loadAccountsFromFile(accounts, &numAccounts, "accounts.txt");

    do {
        // Display menu
        printf("\nBank Management System Menu:\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Check Balance\n");
        printf("5. Display Account Details\n");
        printf("6. Save Accounts to File\n");
        printf("7. Load Accounts from File\n");
        printf("0. Exit\n");
         // Get user choice
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Perform action based on user choice
        switch (choice) {
            case 1:
                createAccount(accounts, &numAccounts);
                break;
            case 2:
                deposit(accounts, numAccounts);
                break;
            case 3:
                withdraw(accounts, numAccounts);
                break;
            case 4:
                checkBalance(accounts, numAccounts);
                break;
            case 5:
                displayAccountDetails(accounts, numAccounts);
                break;
            case 6:
                saveAccountsToFile(accounts, numAccounts, "accounts.txt");
                printf("Accounts saved to file successfully!\n");
                break;
            case 7:
                loadAccountsFromFile(accounts, &numAccounts, "accounts.txt");
                printf("Accounts loaded from file successfully!\n");
                break;
            case 0:
                printf("Exiting Bank Management System. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 0);

    return 0;
}
void createAccount(struct BankAccount *accounts, int *numAccounts) {
    // Get account details from user
    printf("Enter account holder name: ");
    scanf("%s", accounts[*numAccounts].holderName);

    accounts[*numAccounts].accountNumber = *numAccounts + 1;
    accounts[*numAccounts].balance = 0; 

    // Increment the number of accounts
    (*numAccounts)++;

    printf("Account created successfully!\n");
}

void deposit(struct BankAccount *accounts, int numAccounts) {
    int accountNumber;
    float amount;

    // Get account number and amount to deposit
    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    if (accountNumber >= 1 && accountNumber <= numAccounts) {
        printf("Enter amount to deposit: ");
        scanf("%f", &amount);

        accounts[accountNumber - 1].balance += amount;

        printf("Amount deposited successfully! New balance: %.2f\n", accounts[accountNumber - 1].balance);
    } else {
        printf("Invalid account number. Please enter a valid account number.\n");
    }
}
void withdraw(struct BankAccount *accounts, int numAccounts) {
    int accountNumber;
    float amount;

    // Get account number and amount to withdraw
    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    if (accountNumber >= 1 && accountNumber <= numAccounts) {
        printf("Enter amount to withdraw: ");
        scanf("%f", &amount);

        if (amount <= accounts[accountNumber - 1].balance) {
            accounts[accountNumber - 1].balance -= amount;
            printf("Amount withdrawn successfully! New balance: %.2f\n", accounts[accountNumber - 1].balance);
        } else {
            printf("Insufficient balance!\n");
        }
    } else {
        printf("Invalid account number. Please enter a valid account number.\n");
    }
}
void checkBalance(struct BankAccount *accounts, int numAccounts) {
    int accountNumber;

    // Get account number
    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    if (accountNumber >= 1 && accountNumber <= numAccounts) {
        printf("Account balance: %.2f\n", accounts[accountNumber - 1].balance);
    } else {
        printf("Invalid account number. Please enter a valid account number.\n");
    }
}

void displayAccountDetails(struct BankAccount *accounts, int numAccounts) {
    int accountNumber;

    // Get account number
    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    if (accountNumber >= 1 && accountNumber <= numAccounts) {
        printf("Account Number: %d\n", accounts[accountNumber - 1].accountNumber);
        printf("Account Holder Name: %s\n", accounts[accountNumber - 1].holderName);
        printf("Account Balance: %.2f\n", accounts[accountNumber - 1].balance);
    } else {
        printf("Invalid account number. Please enter a valid account number.\n");
    }
}

void saveAccountsToFile(struct BankAccount *accounts, int numAccounts, const char *filename) {
    FILE *file = fopen(filename, "w");

    if (file != NULL) {
        fprintf(file, "%d\n", numAccounts);

        for (int i = 0; i < numAccounts; i++) {
            fprintf(file, "%d %s %.2f\n", accounts[i].accountNumber, accounts[i].holderName, accounts[i].balance);
        }

        fclose(file);
    } else {
        printf("Error opening file for writing.\n");
    }
}

void loadAccountsFromFile(struct BankAccount *accounts, int *numAccounts, const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file != NULL) {
        fscanf(file, "%d", numAccounts);

        for (int i = 0; i < *numAccounts; i++) {
            fscanf(file, "%d %s %f", &accounts[i].accountNumber, accounts[i].holderName, &accounts[i].balance);
            printf("%d %s %f\n",accounts[i].accountNumber, accounts[i].holderName, accounts[i].balance);
        }

        fclose(file);
    } else {
        printf("Error opening file for reading. Starting with an empty account list.\n");
        *numAccounts = 0;
    }
}
