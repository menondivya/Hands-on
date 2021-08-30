
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int MAX_Timer_Count = 60;

void timer_function();
void restart_timer();

struct timer_cred
{
    int timer_id;
    struct tm *timer_start_time;
    struct tm *timer_end_time;
}Timer_1, Timer_2;

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * 1000 * number_of_seconds;
    // Storing start time
    clock_t start_time = clock();
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}

void start_timer(struct timer_cred * ptr)
{
    float sec = 10;
    time_t rawtime;
    //struct tm *start_time, *end_time;
    time( &rawtime );
    ptr->timer_start_time = localtime( &rawtime );
    printf("Current local time of timer(ID: %d)(%s)\n",ptr->timer_id,asctime(ptr->timer_start_time));
    while(sec-0.5>0)
    {
      delay(1);
      sec--;
      MAX_Timer_Count--;
    }
    time( &rawtime );
    ptr->timer_end_time = localtime( &rawtime );
    printf("After delay current local time : %s\n", asctime(ptr->timer_end_time));
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

void restart_timer(struct timer_cred * ptr)
{
    time_t rawtime;
    struct tm *start_time, *end_time;
    time( &rawtime );
    start_time = localtime( &rawtime );
    printf("Current local time (before restart): %d:%d:%d\n", start_time->tm_hour, start_time->tm_min, start_time->tm_sec);
    start_timer(ptr);
}

void timer_function(struct timer_cred *ptr)
{
    char ch;

    while (1)
    {
        printf("\nEnter your choice\n1 - Start Timer\n2 - Stop Timer\n3 - Restart Timer\nESC to exit\n");
        scanf("%c", &ch);

        if((int)ch=='1')
            start_timer(ptr);
        else if((int)ch=='2')
            stop_timer();
        else if((int)ch=='3')
            restart_timer(ptr);
        else if((int)ch==27)
            break;
    }
}

void main ()
{
    Timer_1.timer_id = 300;
    Timer_2.timer_id = 301;

    int timer_choice;
    
    while(1)
    {
        printf("/nWhich timer do you wish to continue with?\n1 - timer 1\n2 - timer 2\n");
        scanf("%d", &timer_choice);
        switch(timer_choice)
        {
            case 1:   timer_function(&Timer_1);
                        break;
            case 2:   timer_function(&Timer_2);
                        break;
            default: printf("invalid option, try again");
                        break;
        }
    }
}