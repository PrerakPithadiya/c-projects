#ifndef BANK_MANAGEMENT_SYSTEM_H
#define BANK_MANAGEMENT_SYSTEM_H

typedef struct
{
    char username[30];
    int accountNumber;
    float balance;
} Account;

void createAccount();
void depositMoney();
void withdrawMoney();
void checkBalance();
void menu();
int isUniqueAccountNumber(int accountNumber);
Account *getAccountByNumber(int accountNumber);
void saveAccount(Account account);

#endif // BANK_MANAGEMENT_SYSTEM_H
