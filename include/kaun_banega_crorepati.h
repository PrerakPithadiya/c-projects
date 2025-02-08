#ifndef KAUN_BANEGA_CROREPATI_H
#define KAUN_BANEGA_CROREPATI_H

#define NUM_QUESTIONS 10
#define TIME_LIMIT 10
#define MAX_LIFELINES 5
#define TOTAL_PRIZE 21100000

typedef struct
{
    char question[256];
    char options[4][50];
    char correctAnswer;
} Question;

void displayTitle();
void display50_50Options(int questionIndex);
int askQuestion(int questionIndex, int *lifelinesUsed);

#endif // KAUN_BANEGA_CROREPATI_H
