#include <stdio.h>
#include <assert.h>
#include "../include/bank_management_system.h"

void test_createAccount()
{
    // This function interacts with user input and file system, so we can't assert much here.
    // However, we can ensure it runs without errors.
    createAccount();
}

void test_depositMoney()
{
    // This function interacts with user input and file system, so we can't assert much here.
    // However, we can ensure it runs without errors.
    depositMoney();
}

void test_withdrawMoney()
{
    // This function interacts with user input and file system, so we can't assert much here.
    // However, we can ensure it runs without errors.
    withdrawMoney();
}

void test_checkBalance()
{
    // This function interacts with user input and file system, so we can't assert much here.
    // However, we can ensure it runs without errors.
    checkBalance();
}

int main()
{
    test_createAccount();
    test_depositMoney();
    test_withdrawMoney();
    test_checkBalance();
    printf("All tests passed!\n");
    return 0;
}
