#include <stdio.h>
#include <assert.h>
#include "../include/progress_bar.h"

void test_progress_bar()
{
    Task task = {0, 100, 10, "Test Task"};
    assert(task.current == 0);
    assert(task.total == 100);
    assert(task.increment == 10);
    assert(task.name != NULL);
}

int main()
{
    test_progress_bar();
    printf("All tests passed!\n");
    return 0;
}
