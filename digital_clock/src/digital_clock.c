/**
 * @file digital_clock.c
 * @brief A digital clock implementation with 12/24 hour format display options
 *
 * This program implements a digital clock that can display time in both 12-hour
 * and 24-hour formats. It uses ANSI escape codes for colored output and supports
 * cross-platform screen clearing for continuous display updates.
 *
 * @author [Prerak Pithadiya]
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // For sleep function on Unix-based systems

/**
 * @defgroup ansi_codes ANSI Escape Codes
 * @{
 * ANSI escape codes for console text styling and coloring
 */
#define RESET "\033[0m"         // Resets all text attributes to default
#define BOLD "\033[1m"          // Bold text
#define GREEN "\033[32m"        // Green text color
#define CYAN "\033[36m"         // Cyan text color
#define YELLOW "\033[33m"       // Yellow text color
#define BORDER_COLOR "\033[34m" // Blue text for borders
#define RED "\033[31m"          // Red text color
#define MAGENTA "\033[35m"      // Magenta text color
#define BLUE "\033[34m"         // Blue text color
#define WHITE "\033[37m"        // White text color
#define BG_BLACK "\033[40m"     // Black background
#define BG_BLUE "\033[44m"      // Blue background
#define UNDERLINE "\033[4m"     // Underlined text
#define BLINK "\033[5m"         // Blinking text
/** @} */

/**
 * @brief Displays time in 12-hour format with AM/PM indicator
 *
 * This function takes the current time information and formats it into a 12-hour
 * display with appropriate AM/PM designation. The output is enhanced with ANSI
 * color codes for better visibility.
 *
 * @param time_info Pointer to a tm structure containing the current time
 */
void display12HourFormat(struct tm *time_info)
{
    char am_pm[] = "AM";
    int hour = time_info->tm_hour;

    // Determine AM or PM and adjust hour to 12-hour format
    if (hour >= 12)
    {
        am_pm[0] = 'P';
    }
    if (hour > 12)
    {
        hour -= 12;
    }
    else if (hour == 0)
    {
        hour = 12;
    }
    printf(BLUE BOLD "Time: " RESET YELLOW BOLD "%02d" RESET RED ":" RESET YELLOW BOLD "%02d" RESET RED ":" RESET YELLOW BOLD "%02d" RESET MAGENTA BOLD " %s\n" RESET, hour, time_info->tm_min, time_info->tm_sec, am_pm);
}

/**
 * @brief Displays time in 24-hour format
 *
 * This function formats and displays the current time in 24-hour format
 * with ANSI color styling for enhanced readability.
 *
 * @param time_info Pointer to a tm structure containing the current time
 */
void display24HourFormat(struct tm *time_info)
{
    printf(BLUE BOLD "Time: " RESET YELLOW BOLD "%02d" RESET RED ":" RESET YELLOW BOLD "%02d" RESET RED ":" RESET YELLOW BOLD "%02d\n" RESET, time_info->tm_hour, time_info->tm_min, time_info->tm_sec);
}

/**
 * @brief Clears the console screen
 *
 * This function provides cross-platform screen clearing functionality.
 * It uses 'cls' command for Windows systems and 'clear' command for Unix-based systems.
 */
void clearScreen()
{
#ifdef _WIN32
    system("cls"); // Windows
#else
    system("clear"); // Unix-based
#endif
}

/**
 * @brief Main program entry point
 *
 * Initializes the digital clock program, handles user input for format selection,
 * and manages the continuous display loop for time updates.
 *
 * The program performs the following steps:
 * 1. Displays a welcome message and format selection menu
 * 2. Accepts user input for time format preference
 * 3. Enters an infinite loop that:
 *    - Clears the screen
 *    - Gets current time
 *    - Displays date and time in selected format
 *    - Updates every second
 *
 * @return int Returns 0 on successful execution
 */
int main()
{
    int format_choice;
    time_t raw_time;
    struct tm *time_info;

    // Display program title and prompt user to select a time format
    printf(RED BOLD UNDERLINE "Digital Clock\n" RESET);
    printf(CYAN BOLD "Choose time format:\n" RESET);
    printf(MAGENTA "1. 12-Hour Format\n" RESET);
    printf(MAGENTA "2. 24-Hour Format (Default)\n" RESET);
    printf(GREEN BOLD "Enter your choice (1 or 2): " RESET);
    scanf("%d", &format_choice);
    // Main program loop
    while (1)
    {
        clearScreen();

        // Get current time and date
        time(&raw_time);
        time_info = localtime(&raw_time);
        // Display current date
        printf(CYAN BOLD "Current Date: " RESET YELLOW BOLD "%04d" MAGENTA "-" YELLOW "%02d" MAGENTA "-" YELLOW "%02d\n" RESET, time_info->tm_year + 1900, time_info->tm_mon + 1, time_info->tm_mday);
        // Display time in selected format
        if (format_choice == 1)
        {
            display12HourFormat(time_info);
        }
        else
        {
            display24HourFormat(time_info);
        }

        fflush(stdout);
        sleep(1);
    }

    return 0;
}