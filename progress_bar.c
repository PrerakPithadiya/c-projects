#include <stdio.h>
#include <unistd.h> // For usleep
#include <stdlib.h> // For rand(), srand()
#include <time.h>   // For time()

#ifdef _WIN32
#include <windows.h>
#define CLEAR_SCREEN "cls"
#else
#include <sys/ioctl.h>
#define CLEAR_SCREEN "clear"
#endif

#define NUM_TASKS 5
#define PROGRESS_BAR_WIDTH 40

typedef struct
{
    int current;
    int total;
    int increment;
    const char *name;
} Task;

const char *spinner[] = {"|", "/", "-", "\\"}; // Animation frames

// Function to clear screen
void clear_screen()
{
    system(CLEAR_SCREEN);
}

// Function to print color-coded progress bar
void print_progress(Task task, int frame)
{
    int filled = (task.current * PROGRESS_BAR_WIDTH) / task.total;
    printf("\033[1;94m%-10s\033[0m", task.name); // Task name in bright blue

    printf(" \033[1;93m%s\033[0m ", spinner[frame % 4]); // Rotating spinner in bright yellow

    printf("[");
    for (int i = 0; i < filled; i++)
        printf("\033[1;92m#\033[0m"); // Bright green filled part
    for (int i = filled; i < PROGRESS_BAR_WIDTH; i++)
        printf("\033[1;90m-\033[0m"); // Bright black (gray) empty part
    printf("]");

    printf(" \033[1;96m%3d%%\033[0m\n", (task.current * 100) / task.total); // Bright cyan percentage
}

// Main function
int main()
{
    srand(time(NULL)); // Seed random generator

    Task tasks[NUM_TASKS] = {
        {0, 100, rand() % 6 + 2, "Task 1"},
        {0, 100, rand() % 6 + 2, "Task 2"},
        {0, 100, rand() % 6 + 2, "Task 3"},
        {0, 100, rand() % 6 + 2, "Task 4"},
        {0, 100, rand() % 6 + 2, "Task 5"}};

    int completed = 0, frame = 0;
    while (completed < NUM_TASKS)
    {
        completed = 0;
        clear_screen();

        for (int i = 0; i < NUM_TASKS; i++)
        {
            if (tasks[i].current < tasks[i].total)
            {
                tasks[i].current += tasks[i].increment;
                if (tasks[i].current > tasks[i].total)
                    tasks[i].current = tasks[i].total;
            }
            else
            {
                completed++;
            }
            print_progress(tasks[i], frame);
        }

        // Overall progress
        int overall = 0;
        for (int i = 0; i < NUM_TASKS; i++)
            overall += tasks[i].current;
        overall = (overall * 100) / (NUM_TASKS * 100);

        // Print overall progress
        printf("\n\033[1;95mOverall Progress:\033[0m \033[1;92m%d%%\033[0m\n", overall); // Bright magenta and bright green

        usleep(200000); // 200ms delay
        frame++;
    }

    // Completion message
    printf("\n\033[1;92mAll tasks completed successfully!\033[0m\n"); // Bright green

    return 0;
}
