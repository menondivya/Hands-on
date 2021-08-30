#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>

#include<sys/types.h> //key_t is essentially an int type defined in <sys/types.h
#include<sys/ipc.h>
#include<sys/msg.h>

#define MAX_TEXT 512

struct my_msg_st
{
    long int my_msg_type;
    char some_text[MAX_TEXT];
};

int main()
{
    int running = 1;
    struct my_msg_st some_data;
    int msgid;
    char buffer[BUFSIZ];
    /*
    int msgget(key_t key, int msgflg)
    key_t key; key to be passed to msgget()
    int msgflg msgflg to be passed to msgget()
    int msqid;  return value from msgget() 
    */
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT); //msgget() -> it returns the message queue ID to the key argument
    /* IPC_CREAT flag is supplied in the flags argument appropriate to the call, the function tries to create the facility 
    if it does not exist already*/
    if(msgid == -1)
    {
        fprintf(stderr, "message failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }

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

        if(msgrcv(msgid, (void *)&some_data, BUFSIZ, msg_to_rcv, 0) == -1)
        {
            fprintf(stderr, "message failed with error at sender side: %d\n", errno);
            exit(EXIT_FAILURE);
        }
        printf("Ack from receiver: %s", some_data.some_text);

        if(strcmp(some_data.some_text, "end", 3) == 0)
        {
            running = 0;
        }    
    }

    exit(EXIT_SUCCESS);
}
