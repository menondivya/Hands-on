#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>

#include<sys/types.h> //key_t is essentially an int type defined in <sys/typ$
#include<sys/ipc.h>
#include<sys/msg.h>

#define MAX_TEXT 512
char buffer[BUFSIZ];
int running =1;
int count=0;

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct my_msg_st
{
    long int my_msg_type;
    char some_text[MAX_TEXT];
};

void *thread1func(void *ptr) //function for sending the data
{
    
    int i;
    int *msgid;
    msgid = (int *)ptr;
    struct my_msg_st some_data;
    while(running)
    {  
        count++;
        printf("Enter some text (call no.:%d) : ", count);
        fgets(buffer, BUFSIZ, stdin);
        some_data.my_msg_type = 1;
        strcpy(some_data.some_text, buffer);

        if(msgsnd(*msgid, (void *)&some_data, MAX_TEXT, 0) == -1)
        {
            fprintf(stderr, "message failed\n");
            exit(EXIT_FAILURE);
        }
        
        if(strncmp(buffer, "end", 3) == 0)
        {
            running = 0;
        }
    }
    
    exit(EXIT_SUCCESS);
}

void *thread2func(void *ptr) //function for receiving the data
{
    pthread_mutex_lock(&mutex);
    int i;
    int *msgid = (int *)ptr;
    struct my_msg_st some_data;
    long int msg_to_rcv = 0;
    
    while(running)
    { 
        count++;
        if(msgrcv(*msgid, (void *)&some_data, BUFSIZ, msg_to_rcv, 0) == -1)
        {
            fprintf(stderr, "message failed with error: %d\n", errno);
            exit(EXIT_FAILURE);
        }
        printf("\nFrom sender (cal no.%d): %s", count, some_data.some_text);
        
        if(strncmp(some_data.some_text, "end", 3) == 0)
        {
            running = 0;
        }
    }
    pthread_mutex_unlock(&mutex);
    exit(EXIT_SUCCESS);
}

int main()
{
    int i, ret1, ret2, msgid[2];
    char buffer[BUFSIZ];
    pthread_t thread1, thread2;
    
    if (pthread_mutex_init(&mutex, NULL) != 0)  
    { 
        printf("\n mutex init has failed\n"); 
        return 1; 
    } 

    msgid[0] = msgget((key_t)1111, 0666 | IPC_CREAT);
    msgid[1] = msgget((key_t)2222, 0666 | IPC_CREAT);
    
    ret1 = pthread_create(&thread1, NULL, thread1func, (void *)msgid);
    thread2func((void *)msgid);
    pthread_join(thread1, NULL); 
    pthread_mutex_destroy(&mutex);
    return 0;
}
