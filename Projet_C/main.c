#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRANSACTION 1000
#define FILENAME "accounts.dat"

// Defining a date
typedef struct {
    int month;
    int day;
    int year;
} Date;

// Function to enter a date with input validation
void enterDate(Date *date) {
    do {
        printf("\nEnter the day: ");
        scanf("%d", &date->day);
    } while (date->day < 1 || date->day > 31);

    do {
        printf("\nEnter the month: ");
        scanf("%d", &date->month);
    } while (date->month < 1 || date->month > 12);

    do {
        printf("\nEnter the year: ");
        scanf("%d", &date->year);
    } while (date->year < 1900 || date->year > 2100);
}

// Function to display a date
void displayDate(const Date *date) {
    printf("%02d/%02d/%04d", date->day, date->month, date->year);
}
// Function to update a date
void updateDate(Date *date) {
    printf("\nEnter the new day: ");
    scanf("%d", &date->day);

    printf("\nEnter the new month: ");
    scanf("%d", &date->month);

    printf("\nEnter the new year: ");
    scanf("%d", &date->year);
}

// Defining an address
typedef struct {
    char street[100]; // Street name
    int number;       // Street number
    char city[50];    // City name
    char postalCode[10];
    char country[50]; // Country name
} Address;

// Function to enter an address with input validation
void enterAddress(Address *address) {
    printf("\nEnter the street name: ");
    scanf("%99s", address->street);

    do {
        printf("\nEnter the street number: ");
        scanf("%d", &address->number);
    } while (address->number <= 0);

    printf("\nEnter the city name: ");
    scanf("%49s", address->city);

    printf("\nEnter the postal code: ");
    scanf("%9s", address->postalCode);

    printf("\nEnter the country name: ");
    scanf("%49s", address->country);
}

// Function to display an address
void displayAddress(const Address *address) {
    printf("\nStreet: %s %d\n", address->street, address->number);
    printf("City: %s\n", address->city);
    printf("Postal Code: %s\n", address->postalCode);
    printf("Country: %s\n", address->country);
}

// Function to update an address
void updateAddress(Address *address) {
    printf("\nEnter the new street name: ");
    scanf("%s", address->street);

    printf("\nEnter the new street number: ");
    scanf("%d", &address->number);

    printf("\nEnter the new city name: ");
    scanf("%s", address->city);

    printf("\nEnter the new postal code: ");
    scanf("%s", address->postalCode);

    printf("\nEnter the new country name: ");
    scanf("%s", address->country);
}

//Defining transaction type
typedef enum {
    DEPOSIT,
    WITHDRAWAL
} TransactionType;

// Defining transactions
typedef struct  {
    double amount;
    TransactionType type;  // Transaction type: DEPOSIT or WITHDRAWAL
} Transaction;
//Function to enter a transaction
void enterTransaction(Transaction *transaction) {
    do {
        printf("\nEnter the transaction amount: ");
        scanf("%lf", &transaction->amount);
    } while (transaction->amount <= 0);

    int typeChoice;
    printf("\nSelect the transaction type:\n");
    printf("1. Deposit\n");
    printf("2. Withdrawal\n");
    printf("Enter your choice (1-2): ");
    scanf("%d", &typeChoice);

    transaction->type = (typeChoice == 1) ? DEPOSIT : WITHDRAWAL;
}

//Function to display a transaction
void displayTransaction(const Transaction *transaction) {
    const char *transactionType = (transaction->type == DEPOSIT) ? "Deposit" : "Withdrawal";
    printf("\nTransaction Type: %s\n", transactionType);
    printf("Amount: %.2lf\n", transaction->amount);
}

// Defining account types
typedef enum {
    SAVINGS,
    CURRENT,
    FIXED_DEPOSIT,
    STUDENT,
    JOINT,
    INVALID_TYPE

} AccountType;

// Defining a bank account
typedef struct  {
    int accNum;                        // accountNumber
    char holderName[50];
    double balance;
    Date dob;                   // date of birth
    Transaction transactions[MAX_TRANSACTION];  // Assuming a fixed size for transactions
    int numTransactions;
    Address address;
    AccountType accType;
} BankAccount;

//Function to enter an account type
AccountType enterAccountType() {
    int choice;

    printf("\nSelect an account type:\n");
    printf("1. Savings Account\n");
    printf("2. Current Account\n");
    printf("3. Fixed Deposit Account\n");
    printf("4. Student Account\n");
    printf("5. Joint Account\n");
    printf("Enter your choice (1-5): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            return SAVINGS;
        case 2:
            return CURRENT;
        case 3:
            return FIXED_DEPOSIT;
        case 4:
            return STUDENT;
        case 5:
            return JOINT;
        default:
            printf("Invalid choice. Defaulting to Savings Account.\n");
            return SAVINGS;
    }
}

// Function to convert AccountType to string for display
const char *accountTypeToString(AccountType accType) {
    switch (accType) {
        case SAVINGS:
            return "Savings Account";
        case CURRENT:
            return "Current Account";
        case FIXED_DEPOSIT:
            return "Fixed Deposit Account";
        case STUDENT:
            return "Student Account";
        case JOINT:
            return "Joint Account";
        default:
            return "Unknown Account Type";
    }
}

// Function to create a new bank account and store it in a file
void createAccount() {
    FILE *file = fopen(FILENAME, "ab+"); // Open file in binary append/update mode

    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    BankAccount newAccount;
    newAccount.numTransactions = 0; // Initialize with 0 transactions

    // Input account information
    printf("\nCreating a New Bank Account\n");

    // Account Holder's Name
    printf("\nEnter the account holder's name: ");
    scanf("%49s", newAccount.holderName);

    // Date of Birth
    printf("\nEnter the date of birth:\n");
    enterDate(&newAccount.dob);

    // Address
    printf("\nEnter the address:\n");
    enterAddress(&newAccount.address);

    // Account Type
    printf("\nSelect the account type:\n");
    newAccount.accType = enterAccountType();

    // Generate a unique account number
    fseek(file, -sizeof(BankAccount), SEEK_END);
    if (fread(&newAccount, sizeof(BankAccount), 1, file) == 1) {
        newAccount.accNum++; // Increment the account number
    } else {
        newAccount.accNum = 1; // Start with 1 if no accounts exist yet
    }

    // Display entered information for confirmation
    printf("\nAccount Information Entered:\n");
    printf("Account Holder: %s\n", newAccount.holderName);
    printf("Date of Birth: ");
    displayDate(&newAccount.dob);
    printf("\n");
    displayAddress(&newAccount.address);
    printf("Account Type: %s\n", accountTypeToString(newAccount.accType));

    // Confirmation prompt
    char confirm;
    printf("\nDo you want to confirm and create this account? (Y/N): ");
    scanf(" %c", &confirm);

    if (confirm == 'Y' || confirm == 'y') {
        // Write the new account to the file
        fseek(file, 0, SEEK_END);
        fwrite(&newAccount, sizeof(BankAccount), 1, file);

        printf("\nAccount created successfully!\n");
        printf("Account Number: %d\n", newAccount.accNum); // Display the account number
    } else {
        printf("\nAccount creation canceled.\n");
    }

    fclose(file);
}


// Function to display information for a specific bank account
void displayAccountInfo(int accountNumber) {
    FILE *file = fopen(FILENAME, "rb"); // Open file in binary read mode

    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    BankAccount account;

    // Find the account with the given account number
    while (fread(&account, sizeof(BankAccount), 1, file) == 1) {
        if (account.accNum == accountNumber) {
            // Display account information
            printf("\nBank Account Information for Account Number %d:\n", accountNumber);
            printf("Account Holder: %s\n", account.holderName);
            printf("Balance: %.2lf\n", account.balance);
            printf("Date of Birth: ");
            displayDate(&account.dob);
            printf("\n");
            displayAddress(&account.address);
            printf("Account Type: %s\n", accountTypeToString(account.accType));
            printf("Number of Transactions: %d\n", account.numTransactions);

            // Display transactions
            printf("\nTransactions:\n");
            for (int i = 0; i < account.numTransactions; ++i) {
                displayTransaction(&account.transactions[i]);
            }

            fclose(file);
            return;
        }
    }

    // Account not found
    printf("Account with number %d not found.\n", accountNumber);
    fclose(file);
}

// Function to update information for a specific bank account
void updateAccount(int accountNumber) {
    FILE *file = fopen(FILENAME, "r+b"); // Open file in binary read/write mode

    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    BankAccount account;

    // Find the account with the given account number
    while (fread(&account, sizeof(BankAccount), 1, file) == 1) {
        if (account.accNum == accountNumber) {
            // Display current account information
            printf("\nCurrent Bank Account Information for Account Number %d:\n", accountNumber);
            printf("Account Holder: %s\n", account.holderName);
            printf("Balance: %.2lf\n", account.balance);
            printf("Date of Birth: ");
            displayDate(&account.dob);
            printf("\n");
            displayAddress(&account.address);
            printf("Account Type: %s\n", accountTypeToString(account.accType));

            // Input updated account information
            printf("\nUpdating Bank Account Information for Account Number %d:\n", accountNumber);

            enterDate(&account.dob);
            enterAddress(&account.address);
            account.accType = enterAccountType();

            // Write the updated account back to the file
            fseek(file, -sizeof(BankAccount), SEEK_CUR);
            fwrite(&account, sizeof(BankAccount), 1, file);

            printf("\nAccount updated successfully!\n");

            fclose(file);
            return;
        }
    }

    // Account not found
    printf("Account with number %d not found.\n", accountNumber);
    fclose(file);
}

// Function to delete a specific bank account
void deleteAccount(int accountNumber) {
    FILE *file = fopen(FILENAME, "r+b"); // Open file in binary read/write mode

    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    BankAccount account;
    FILE *tempFile = fopen("temp.dat", "wb"); // Temporary file for rewriting data

    if (tempFile == NULL) {
        perror("Error creating temporary file");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Find the account with the given account number
    while (fread(&account, sizeof(BankAccount), 1, file) == 1) {
        if (account.accNum != accountNumber) {
            // Copy all accounts except the one to be deleted to the temporary file
            fwrite(&account, sizeof(BankAccount), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Remove the original file and rename the temporary file
    remove(FILENAME);
    rename("temp.dat", FILENAME);

    printf("Account with number %d has been deleted.\n", accountNumber);
}

// Function to display information for all bank accounts
void showAllAccounts() {
    FILE *file = fopen(FILENAME, "rb"); // Open file in binary read mode

    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    BankAccount account;

    printf("\nAll Bank Accounts:\n");

    // Display information for all accounts
    while (fread(&account, sizeof(BankAccount), 1, file) == 1) {
        printf("\nAccount Number: %d\n", account.accNum);
        printf("Account Holder: %s\n", account.holderName);
        printf("Balance: %.2lf\n", account.balance);
        printf("Date of Birth: ");
        displayDate(&account.dob);
        printf("\n");
        displayAddress(&account.address);
        printf("Account Type: %s\n", accountTypeToString(account.accType));
        printf("Number of Transactions: %d\n", account.numTransactions);
    }

    fclose(file);
}

// Function to display the transaction history for a specific bank account
void displayTransactionHistory(int accountNumber) {
    FILE *file = fopen(FILENAME, "rb"); // Open file in binary read mode

    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    BankAccount account;

    // Find the account with the given account number
    while (fread(&account, sizeof(BankAccount), 1, file) == 1) {
        if (account.accNum == accountNumber) {
            printf("\nTransaction History for Account Number %d:\n", accountNumber);

            // Display transactions
            for (int i = 0; i < account.numTransactions; ++i) {
                printf("Transaction %d:\n", i + 1);
                displayTransaction(&account.transactions[i]);
                printf("\n");
            }

            fclose(file);
            return;
        }
    }

    // Account not found
    printf("Account with number %d not found.\n", accountNumber);
    fclose(file);
}

// Function to display accounts by type
void displayAccountsByType(AccountType type) {
    FILE *file = fopen(FILENAME, "rb"); // Open file in binary read mode

    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    BankAccount account;
    int found = 0;

    // Display accounts of the specified type
    while (fread(&account, sizeof(BankAccount), 1, file) == 1) {
        if (account.accType == type) {
            printf("\nAccount Number: %d\n", account.accNum);
            printf("Account Holder: %s\n", account.holderName);
            printf("Balance: %.2lf\n", account.balance);
            printf("Date of Birth: ");
            displayDate(&account.dob);
            printf("\n");
            displayAddress(&account.address);
            printf("Account Type: %s\n", accountTypeToString(account.accType));
            printf("Number of Transactions: %d\n", account.numTransactions);
            found = 1;
        }
    }

    fclose(file);

    if (!found) {
        printf("No accounts found for the specified type.\n");
    }
}

// Function to perform a transaction for a specific bank account
void performTransaction(int accountNumber) {
    FILE *file = fopen(FILENAME, "r+b"); // Open file in binary read/write mode

    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    BankAccount account;

    // Find the account with the given account number
    while (fread(&account, sizeof(BankAccount), 1, file) == 1) {
        if (account.accNum == accountNumber) {
            // Display current account information
            printf("\nCurrent Bank Account Information for Account Number %d:\n", accountNumber);
            printf("Account Holder: %s\n", account.holderName);
            printf("Balance: %.2lf\n", account.balance);
            printf("Date of Birth: ");
            displayDate(&account.dob);
            printf("\n");
            displayAddress(&account.address);
            printf("Account Type: %s\n", accountTypeToString(account.accType));

            // Input transaction details
            Transaction newTransaction;
            enterTransaction(&newTransaction);

            // Update account balance and transaction history
            if (newTransaction.type == DEPOSIT) {
                account.balance += newTransaction.amount;
            } else if (newTransaction.type == WITHDRAWAL) {
                if (account.balance >= newTransaction.amount) {
                    account.balance -= newTransaction.amount;
                } else {
                    printf("Insufficient funds for withdrawal. Transaction canceled.\n");
                    fclose(file);
                    return;
                }
            }

            // Update transaction history
            if (account.numTransactions < MAX_TRANSACTION) {
                account.transactions[account.numTransactions++] = newTransaction;
            } else {
                printf("Transaction history is full. Unable to add new transaction.\n");
            }

            // Write the updated account back to the file
            fseek(file, -sizeof(BankAccount), SEEK_CUR);
            fwrite(&account, sizeof(BankAccount), 1, file);

            printf("\nTransaction completed successfully!\n");

            fclose(file);
            return;
        }
    }

    // Account not found
    printf("Account with number %d not found.\n", accountNumber);
    fclose(file);
}


//The main function and the menu
int main() {
    int choice, accountNumber;

    do {
        printf("\n********************************************************\n");
        printf("\n               Bank Management System\n");
        printf("\n********************************************************\n");
        printf("1. Create a New Account\n");
        printf("2. Display Account Information\n");
        printf("3. Update Account Information\n");
        printf("4. Delete an Account\n");
        printf("5. Show All Accounts\n");
        printf("6. Display Transaction History\n");
        printf("7. Display Accounts by Type\n");
        printf("8. Perform a Transaction\n");
        printf("9. Exit\n");
        printf("Enter the number corresponding to your choice (1-9): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nYou chose to create a new account.\n");
                createAccount();
                break;
            case 2:
                printf("\nYou chose to display account information.\n");
                printf("Enter the account number you want to display: ");
                scanf("%d", &accountNumber);
                displayAccountInfo(accountNumber);
                break;
            case 3:
                printf("\nYou chose to update account information.\n");
                printf("Enter the account number you want to update: ");
                scanf("%d", &accountNumber);
                updateAccount(accountNumber);
                break;
            case 4:
                printf("\nYou chose to delete an account.\n");
                printf("Enter the account number you want to delete: ");
                scanf("%d", &accountNumber);
                deleteAccount(accountNumber);
                break;
            case 5:
                printf("\nYou chose to show all accounts.\n");
                showAllAccounts();
                break;
            case 6:
                printf("\nYou chose to display transaction history.\n");
                printf("Enter the account number to display transaction history: ");
                scanf("%d", &accountNumber);
                displayTransactionHistory(accountNumber);
                break;
            case 7:
                printf("\nYou chose to display accounts by type.\n");
                printf("Select the account type:\n");
                printf("1. Savings Account\n");
                printf("2. Current Account\n");
                printf("3. Fixed Deposit Account\n");
                printf("4. Student Account\n");
                printf("5. Joint Account\n");
                printf("Enter your choice (1-5): ");
                scanf("%d", &choice);
                displayAccountsByType((AccountType)(choice - 1));
                break;
            case 8:
                printf("\nYou chose to perform a transaction.\n");
                printf("Enter the account number to perform a transaction: ");
                scanf("%d", &accountNumber);
                performTransaction(accountNumber);
                break;
            case 9:
                printf("Exiting the Bank Account Management System. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 9.\n");
        }
    } while (choice != 9);

    return 0;
}
