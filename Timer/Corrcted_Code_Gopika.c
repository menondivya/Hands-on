#include <stdio.h>

#include <time.h>


void callback(char*time)

{

    printf("call back triggered at:%s",time);

}

void timed_callback(void(*ptr)(char*time))

{

    time_t currenttime;

    time(&currenttime);

    struct tm*timeinfo;

    timeinfo = localtime(&currenttime);

    (*ptr)(ctime(timeinfo));//callback

}

int main(void)

{

    int delay;

    time_t currenttime;

    struct tm*timeinfo;

    time(&currenttime);

    timeinfo = localtime(&currenttime);
 
    printf("Enter the time delay required in s");

    scanf("%d",&delay);

    printf("timer staring time = %s",ctime(&currenttime));

    usleep(delay*1000*1000);

    void(*ptr)(char*time) = &callback;

    timed_callback(ptr);
    
return(0);

}