#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>

#include<sys/types.h> //key_t is essentially an int type defined in <sys/types.h
#include<sys/ipc.h>
#include<sys/msg.h>

#define MAX_TEXT 512
char buffer[BUFSIZ];
int running =1;

struct my_msg_st
{
    long int my_msg_type;
    char some_text[MAX_TEXT];
};

void *thread1func(void *ptr) //function for sending the data
{ 
    int i;
    int msgid = (int *)ptr;
    struct my_msg_st some_data;
    while(running)
    {
        printf("Enter some text: ");
        fgets(buffer, BUFSIZ, stdin);
        some_data.my_msg_type = 1;
        strcpy(some_data.some_text, buffer);
            
        if(msgsnd(msgid, (void *)&some_data, MAX_TEXT, 0) == -1)
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
    int i;
    int msgid = (int *)ptr;
    struct my_msg_st some_data;
    long int msg_to_rcv = 0;

    while(running)
    {
            
        if(msgrcv(msgid, (void *)&some_data, BUFSIZ, msg_to_rcv, 0) == -1)
        {
            fprintf(stderr, "message failed with error: %d\n", errno);
            exit(EXIT_FAILURE);
        }
        printf("From sender: %s", some_data.some_text);
        if(strncmp(some_data.some_text, "end", 3) == 0)
        {
            running = 0;
        }  
    }
    exit(EXIT_SUCCESS);
} 

int main()
{
    int i, ret1, ret2, msgid[2];
    char buffer[BUFSIZ];
    pthread_t thread1, thread2;

    msgid[0] = msgget((key_t)1111, 0666 | IPC_CREAT);
    msgid[1] = msgget((key_t)2222, 0666 | IPC_CREAT);

    ret1 = pthread_create(&thread1, NULL, thread1func, (void *)msgid);
    ret2 = pthread_create(&thread2, NULL, thread2func, (void *)msgid);

    pthread_join(thread1, NULL); 
    pthread_join(thread2, NULL); 
    
    return 0;
}