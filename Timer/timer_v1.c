#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void callback(char*time)
{
 printf("call back triggered at:%s",time);
}

void timed_callback(void(ptr)(char*time))
{
 time_t rawtime;
 struct tm*timeinfo;
 time(&rawtime);
 timeinfo = localtime (&rawtime);
 (*ptr)(asctime(timeinfo));//call back
}

int main(void)
{
 int delay;
 time_t rawtime;
 struct tm* current_time, stop_time;
 time(&rawtime);
 timeinfo = localtime(&rawtime);
 printf("Enter the time delay required in s");
 scanf("%d",&delay);
 printf("timer started at:%s",asctime(timeinfo));
 usleep(delay*1000*1000);
 void(*ptr)(char*time)=&callback;
 timed_callback(ptr);
 return 0;
}
