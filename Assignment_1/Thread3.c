#include<stdlib.h> 
#include<pthread.h>
#include<stdio.h> 
#include <unistd.h> 

void *myfunc(void *myvar); 
int main(int argc, char *argv[]) 
{ 
    pthread_t thread1, thread2;
    char *msg1 = "First Thread";
    char *msg2 = "Second Thread";
    int ret1, ret2; 

    ret1 = pthread_create(&thread1, NULL, myfunc, (void *)msg1);  
    ret2 = pthread_create(&thread2, NULL, myfunc, (void *)msg2); 

    printf("Main after pthread_create");
    
    pthread_join(thread1, NULL); 
    pthread_join(thread2, NULL); 
    
    printf("First thread return value:%d\n", ret1);
    printf("Second thread return value:%d\n", ret2); 
    return 0;
}

void *myfunc(void *myvar) 
{ 
    char *msg;
    msg = (char*)myvar; 
    int i; 
    for (i=0; i<5; i++) 
    {
        printf("%s %d\n", msg, i); 
        sleep(1);
    } 
    return NULL;
} 