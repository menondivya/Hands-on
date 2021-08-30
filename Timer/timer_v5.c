#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * 1000 * number_of_seconds;
    // Storing start time
    clock_t start_time = clock();
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}

int main(void)
{
    int seconds;
    time_t rawtime;
    struct tm * start_time, * end_time;
    time(&rawtime);

    printf("Enter the time delay required in s ");
    scanf("%d",&seconds);
    start_time = localtime(&rawtime);
    printf("\ntimer started at: %s", asctime(start_time));
    
    while (seconds-2>0)
    {
        delay(1);
        seconds--;
    }
    time(&rawtime);
    end_time = localtime(&rawtime);
    printf("\ntimer ended at: %s", asctime(end_time));

    return 0;
}