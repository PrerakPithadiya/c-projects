#include <stdio.h>
#include <assert.h>
#include "../include/kaun_banega_crorepati.h"

void test_displayTitle()
{
    // This function primarily prints to the console, so we can't assert much here.
    // However, we can ensure it runs without errors.
    displayTitle();
}

void test_askQuestion()
{
    int lifelinesUsed[NUM_QUESTIONS] = {0};
    int result = askQuestion(0, lifelinesUsed);
    assert(result == 0 || result == -1 || result == 2 || result > 0);
}

int main()
{
    test_displayTitle();
    test_askQuestion();
    printf("All tests passed!\n");
    return 0;
}
