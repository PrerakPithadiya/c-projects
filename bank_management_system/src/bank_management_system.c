/**
 * @file bank_management_system.c
 * @brief A simple bank management system implementing basic banking operations
 *
 * This program provides functionality for creating bank accounts, depositing and
 * withdrawing money, and checking account balances. All account data is stored
 * in a binary file for persistence.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** @brief Filename for storing account data */
#define FILENAME "accounts.dat"

/* Color codes for styling console output */
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"

/**
 * @struct Account
 * @brief Structure to hold bank account information
 *
 * @var username The account holder's name
 * @var accountNumber Unique identifier for the account
 * @var balance Current balance in the account
 */
typedef struct
{
    char username[30];
    int accountNumber;
    float balance;
} Account;

/* Function prototypes */
void createAccount();
void depositMoney();
void withdrawMoney();
void checkBalance();
void menu();
int isUniqueAccountNumber(int accountNumber);
Account *getAccountByNumber(int accountNumber);
void saveAccount(Account account);

/**
 * @brief Main entry point of the program
 * @return 0 on successful execution
 */
int main()
{
    menu();
    return 0;
}

/**
 * @brief Displays the main menu and handles user input
 *
 * Presents a loop that continuously shows available options and processes
 * user selections until the program is explicitly terminated.
 */
void menu()
{
    int choice;
    while (1)
    {
        printf("\n%s%s*** Bank Management System ***%s\n", BOLD, CYAN, RESET);
        printf("%s1. Create Account%s\n", YELLOW, RESET);
        printf("%s2. Deposit Money%s\n", YELLOW, RESET);
        printf("%s3. Withdraw Money%s\n", YELLOW, RESET);
        printf("%s4. Check Balance%s\n", YELLOW, RESET);
        printf("%s5. Exit%s\n", YELLOW, RESET);
        printf("%sEnter your choice: %s", BOLD, RESET);
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            createAccount();
            break;
        case 2:
            depositMoney();
            break;
        case 3:
            withdrawMoney();
            break;
        case 4:
            checkBalance();
            break;
        case 5:
            printf("%sExiting program. Goodbye!%s\n", GREEN, RESET);
            exit(0);
        default:
            printf("%sInvalid choice. Please try again.%s\n", RED, RESET);
        }
    }
}

/**
 * @brief Creates a new bank account
 *
 * Prompts user for account details, validates the account number for uniqueness,
 * and saves the new account to the database file.
 */
void createAccount()
{
    Account newAccount;
    printf("%sEnter username: %s", BOLD, RESET);
    scanf("%s", newAccount.username);
    printf("%sEnter account number: %s", BOLD, RESET);
    scanf("%d", &newAccount.accountNumber);

    if (!isUniqueAccountNumber(newAccount.accountNumber))
    {
        printf("%s%sAccount number already in use. Try again with a unique number.%s\n", BOLD, RED, RESET);
        return;
    }

    newAccount.balance = 0.0;
    saveAccount(newAccount);

    printf("%s%sAccount created successfully!%s\n", BOLD, GREEN, RESET);
    printf("Username: %s, Account Number: %d, Balance: %.2f\n", newAccount.username, newAccount.accountNumber, newAccount.balance);
}

/**
 * @brief Handles money deposits into an account
 *
 * Validates the account number and deposit amount before updating the account balance.
 */
void depositMoney()
{
    int accountNumber;
    float amount;
    printf("%sEnter account number: %s", BOLD, RESET);
    scanf("%d", &accountNumber);

    Account *account = getAccountByNumber(accountNumber);
    if (account == NULL)
    {
        printf("%sAccount not found.%s\n", RED, RESET);
        return;
    }

    printf("%sEnter amount to deposit: %s", BOLD, RESET);
    scanf("%f", &amount);
    if (amount <= 0)
    {
        printf("%sInvalid amount.%s\n", RED, RESET);
        free(account);
        return;
    }

    account->balance += amount;
    saveAccount(*account);
    printf("%s%sDeposit successful!%s New balance: %.2f\n", BOLD, GREEN, RESET, account->balance);
    free(account);
}

/**
 * @brief Handles money withdrawals from an account
 *
 * Validates the account number and withdrawal amount, ensuring sufficient funds
 * are available before processing the withdrawal.
 */
void withdrawMoney()
{
    int accountNumber;
    float amount;
    printf("%sEnter account number: %s", BOLD, RESET);
    scanf("%d", &accountNumber);

    Account *account = getAccountByNumber(accountNumber);
    if (account == NULL)
    {
        printf("%sAccount not found.%s\n", RED, RESET);
        return;
    }

    printf("%sEnter amount to withdraw: %s", BOLD, RESET);
    scanf("%f", &amount);
    if (amount <= 0 || amount > account->balance)
    {
        printf("%sInvalid amount. Withdrawal exceeds balance.%s\n", RED, RESET);
        free(account);
        return;
    }

    account->balance -= amount;
    saveAccount(*account);
    printf("%s%sWithdrawal successful!%s New balance: %.2f\n", BOLD, GREEN, RESET, account->balance);
    free(account);
}

/**
 * @brief Displays the current balance for a specified account
 */
void checkBalance()
{
    int accountNumber;
    printf("%sEnter account number: %s", BOLD, RESET);
    scanf("%d", &accountNumber);

    Account *account = getAccountByNumber(accountNumber);
    if (account == NULL)
    {
        printf(BOLD "%sAccount not found.%s\n", RED, RESET);
        return;
    }

    printf(BOLD "%sAccount balance: %.2f%s\n", GREEN, account->balance, RESET);
    free(account);
}

/**
 * @brief Checks if an account number is unique in the system
 * @param accountNumber The account number to validate
 * @return 1 if unique, 0 if already exists
 */
int isUniqueAccountNumber(int accountNumber)
{
    FILE *file = fopen(FILENAME, "rb");
    if (!file)
        return 1;

    Account temp;
    while (fread(&temp, sizeof(Account), 1, file))
    {
        if (temp.accountNumber == accountNumber)
        {
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 1;
}

/**
 * @brief Retrieves account information by account number
 * @param accountNumber The account number to search for
 * @return Pointer to Account structure if found, NULL otherwise
 */
Account *getAccountByNumber(int accountNumber)
{
    FILE *file = fopen(FILENAME, "rb");
    if (!file)
        return NULL;

    Account *account = (Account *)malloc(sizeof(Account));
    while (fread(account, sizeof(Account), 1, file))
    {
        if (account->accountNumber == accountNumber)
        {
            fclose(file);
            return account;
        }
    }

    fclose(file);
    free(account);
    return NULL;
}

/**
 * @brief Saves or updates account information in the database file
 * @param account The account structure to save
 *
 * If the account number already exists, the record is updated;
 * otherwise, a new record is appended to the file.
 */
void saveAccount(Account account)
{
    FILE *file = fopen(FILENAME, "r+b");
    if (!file)
        file = fopen(FILENAME, "wb");

    Account temp;
    int found = 0;

    while (fread(&temp, sizeof(Account), 1, file))
    {
        if (temp.accountNumber == account.accountNumber)
        {
            fseek(file, -(long int)sizeof(Account), SEEK_CUR);
            fwrite(&account, sizeof(Account), 1, file);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        fwrite(&account, sizeof(Account), 1, file);
    }

    fclose(file);
}