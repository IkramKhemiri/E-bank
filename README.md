#Project Overview:
The E-Bank Management System, implemented in C, provides users with a comprehensive platform for managing bank accounts. The system is designed with a user-friendly console-based interface, allowing users to perform key operations such as creating accounts, updating information, executing transactions, and retrieving account details. The project employs various structures and functions to facilitate efficient data handling and user interaction.

#Parts_Explication:
1.Date and Address Structures:
The Date structure represents a date with day, month, and year.
The Address structure represents an address with street name, street number, city, postal code, and country.

2.Functions for Date and Address:
enterDate: Allows the user to input a date with input validation.
displayDate: Prints the date in the format DD/MM/YYYY.
updateDate: Allows the user to update a date.
enterAddress: Allows the user to input an address with input validation for the street number.
displayAddress: Prints the address.
updateAddress: Allows the user to update an address.

3.TransactionType Enumeration:
Enumerates transaction types as DEPOSIT and WITHDRAWAL.

4.Transaction Structure:
The Transaction structure represents a transaction with fields for the transaction amount and type.

5.Functions for Transaction:
enterTransaction: Allows the user to input a transaction with input validation for the amount and type.
displayTransaction: Prints information about a transaction, including the type (DEPOSIT or WITHDRAWAL) and amount.

6.AccountType Enumeration:
Enumerates account types as SAVINGS, CURRENT, FIXED_DEPOSIT, STUDENT, JOINT, and INVALID_TYPE.

7.BankAccount Structure:
The BankAccount structure represents a bank account with fields for account number, account holder's name, balance, date of birth (Date), an array of transactions (Transaction), number of transactions, address (Address), and account type (AccountType).

8.File Handling:
The program uses a binary file (accounts.dat) to store and retrieve bank account information.

9.Input Validation:
Several functions include input validation to ensure user inputs are within valid ranges.

10.Main Menu (main Function):
The main function implements a menu-driven Bank Account Management System.
Options include creating a new account, displaying account information, updating account details, deleting an account, showing all accounts, displaying transaction history, displaying accounts by type, performing a transaction, and exiting the system.

11.createAccount Function:
Creates a new bank account, allows the user to input account details, generates a unique account number, writes the account to a file, and displays the account number after successful creation.

12.Additional Functions:
displayAccountInfo: Displays information for a specific bank account identified by the account number.

updateAccount: Allows the user to update information for a specific bank account identified by the account number.

deleteAccount: Deletes a specific bank account identified by the account number.

showAllAccounts: Displays information for all bank accounts stored in the file.

displayTransactionHistory: Displays the transaction history for a specific bank account identified by the account number.

displayAccountsByType: Displays information for all bank accounts of a specific type.

performTransaction: Allows the user to perform a deposit or withdrawal for a specific bank account identified by the account number.