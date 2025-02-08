#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

typedef struct
{
    int current;
    int total;
    int increment;
    const char *name;
} Task;

void clear_screen();
void print_progress(Task task, int frame);

#endif // PROGRESS_BAR_H
