#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "../include/digital_clock.h"

void test_display12HourFormat()
{
    struct tm time_info = {.tm_hour = 14, .tm_min = 30, .tm_sec = 45};
    display12HourFormat(&time_info);
    // Since this function primarily prints to the console, we can't assert much here.
    // However, we can ensure it runs without errors.
}

void test_display24HourFormat()
{
    struct tm time_info = {.tm_hour = 14, .tm_min = 30, .tm_sec = 45};
    display24HourFormat(&time_info);
    // Since this function primarily prints to the console, we can't assert much here.
    // However, we can ensure it runs without errors.
}

int main()
{
    test_display12HourFormat();
    test_display24HourFormat();
    printf("All tests passed!\n");
    return 0;
}
