#ifndef DIGITAL_CLOCK_H
#define DIGITAL_CLOCK_H

void display12HourFormat(struct tm *time_info);
void display24HourFormat(struct tm *time_info);
void clearScreen();

#endif // DIGITAL_CLOCK_H
