
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void timer_function();
void restart_timer();

struct timer_ID
{
    char timer_id;
    struct tm *timer_start_time;
    struct tm *timer_end_time;
}T300, T301;

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * 1000 * number_of_seconds;
    // Storing start time
    clock_t start_time = clock();
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}

void start_timer()
{
    float sec = 10;
    time_t rawtime;
    struct tm *start_time, *end_time;
    time( &rawtime );
    start_time = localtime( &rawtime );
    printf("Current local time : %d:%d:%d\n", start_time->tm_hour, start_time->tm_min, start_time->tm_sec);
    while(sec-0.5>0)
    {
       delay(1);
       sec--;
    }
    time( &rawtime );
    end_time = localtime( &rawtime );
    printf("After 10sec delay current local time : %d:%d:%d\n", end_time->tm_hour, end_time->tm_min, end_time->tm_sec);
}

void stop_timer()
{
    time_t rawtime;
    struct tm *start_time, *end_time;
    time( &rawtime );
    start_time = localtime( &rawtime );
    printf("Timer stopped at : %d:%d:%d\n", start_time->tm_hour, start_time->tm_min, start_time->tm_sec);
    exit(0);
}

void restart_timer()
{
    time_t rawtime;
    struct tm *start_time, *end_time;
    time( &rawtime );
    start_time = localtime( &rawtime );
    printf("Current local time (before restart): %d:%d:%d\n", start_time->tm_hour, start_time->tm_min, start_time->tm_sec);
    start_timer();
}

void timer_function()
{
    char ch;

    while (1)
    {
        printf("\nEnter your choice\n1 - Start Timer\n2 - Stop Timer\n3 - Restart Timer\nESC to exit\n");
        scanf("%c", &ch);

        if((int)ch=='1')
            start_timer();
        else if((int)ch=='2')
            stop_timer();
        else if((int)ch=='3')
            restart_timer();
        else if((int)ch==27)
            break;
    }
}

void main ()
{
   timer_function();
}