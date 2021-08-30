#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#define MAX_TEXT 512

struct my_msg_st
{
    long int my_msg_type;
    char some_text[BUFSIZ];
};

int main()
{
    int running = 1;
    int msgid[2], i;
    char buffer[BUFSIZ];
    struct my_msg_st some_data;
    long int msg_to_rcv = 0;

    msgid[0] = msgget((key_t)1111, 0666 | IPC_CREAT);
    msgid[1] = msgget((key_t)2222, 0666 | IPC_CREAT); 

    if(msgid[0] == -1)
    {
        fprintf(stderr, "message failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    if(msgid[1] == -1)
    {
        fprintf(stderr, "message failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    while(running)
    {
        for(i=0; i<2; i++)
        {
            if(msgrcv(msgid[i], (void *)&some_data, BUFSIZ, msg_to_rcv, 0) == -1)
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
    }

    if(msgctl(msgid, IPC_RMID, 0) == -1) // The msgctl() function alters the permissions and other characteristics of a message queue
    {
        fprintf(stderr, "msgctl(UPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}