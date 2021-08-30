#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>

#include<sys/types.h> //key_t is essentially an int type defined in <sys/typ$
#include<sys/ipc.h>
#include<sys/msg.h>

#define COUNT_TO 100000
#define MAX_CORES 12

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
long long i = 0;

void *start_counting(void *arg)
{
    for(;;)
    {
        if(i>=COUNT_TO)
        {
            return NULL;
        }
        ++i;
        printf("i=%d\n",i);
    }
}

int main(void)()
{
    int i = 0;
    pthread_t *thread_group = malloc(sizeof(pthread_t) * MAX_CORES);

    for (i=0; i<MAX_CORES; ++i)
    {
        pthread_create(&thread_group[i], NULL, start_counting, NULL);
    }
    for (i=0; i<MAX_CORES; ++i)
    {
        pthread_join(&thread_group[i], NULL);
    } 
    return EXIT_SUCCESS;
}