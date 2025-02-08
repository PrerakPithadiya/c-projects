#include <stdio.h>
#include <assert.h>
#include "../include/number_guessing_game.h"

void test_generateRandomNumber()
{
    int num = generateRandomNumber(100);
    assert(num >= 1 && num <= 100);
}

void test_getMaxAttempts()
{
    assert(getMaxAttempts('E') == 10);
    assert(getMaxAttempts('M') == 7);
    assert(getMaxAttempts('H') == 5);
    assert(getMaxAttempts('X') == 7); // Default case
}

int main()
{
    test_generateRandomNumber();
    test_getMaxAttempts();
    printf("All tests passed!\n");
    return 0;
}
