#include <stdio.h>
#include <time.h>

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
  
    // Storing start time
    clock_t start_time = clock();
  
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}

int main(void)
{
    struct tm* current_time, exp_time;
    time_t t;
    int seconds, end_second;
    t = time(NULL);
    current_time = localtime(&t);
    printf("Enter the seconds you want to wait: ");
    scanf("%d", &seconds);
    printf("%s\n", asctime(current_time));
    //end_second = current_time->tm_sec)+seconds;
    exp_time = current_time + (current_time->tm_sec+seconds);
    printf("Expected = %s\n", asctime(exp_time));
    
    // while((ptr->tm_sec) != end_time)
    // {
    //     printf("%d\n", ptr->tm_sec);
    //     delay(1);
    // }
    // printf("end time is : %s\n",asctime(ptr));
    return 0;
}