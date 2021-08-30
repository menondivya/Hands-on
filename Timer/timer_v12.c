
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
};

struct timer_cred timer_creat(int id)
{
    struct timer_cred Timer;
    Timer.timer_id = id;
    time_t rawtime;
    time( &rawtime );
    Timer.timer_start_time = localtime( &rawtime );
    printf("start time of timer(ID: %d): %s", id, asctime(Timer.timer_start_time));
    return Timer;
}

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
    while (1)
    {   
        char ch;
        printf("\nEnter your choice\n1 - Start Timer\n2 - Stop Timer\n3 - Restart Timer\nESC to exit\n");
        scanf("%c", &ch);
        
        if(ch == '1')
            start_timer(ptr);
        else if(ch == '2')
            stop_timer();
        else if(ch == '3')
            restart_timer(ptr);
        else if(ch==27)
            break;
    }
}

void main ()
{
    // Timer_1.timer_id = 300;
    // Timer_2.timer_id = 301;
    
    int timer_choice;
    int id1, id2;
    struct timer_cred timer_1, timer_2;
    
    printf("enter the timer id:");
    scanf("%d", &id1);
    timer_1 = timer_creat(id1);
    
    printf("enter the timer id:");
    scanf("%d", &id2);
    timer_2 = timer_creat(id2);

    while(1)
    {
        printf("\nWhich timer do you wish to continue with?\n1 - timer 1\n2 - timer 2\n");
        scanf("%d", &timer_choice);
        switch(timer_choice)
        {
            case 1:   timer_function(&timer_1);
                        break;
            case 2:   timer_function(&timer_2);
                        break;
            default: printf("\nInvalid option, try again\n");
                        break;
        }
    }
}