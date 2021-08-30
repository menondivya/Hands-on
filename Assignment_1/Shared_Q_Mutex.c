#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Code136_Queue.h"

#define MAX 10

// Declaring global variables
int sum_B = 0, sum_C = 0;
int consumerCount1 = 0;
int consumerCount2 = 0;
int count =0;

// Declare these as static so no code outside of this source
// can access them.
static QNode *head, *tail;    // Declare global pointers to head and tail of queue

//--------------------------------------------
// Function: InitQueue()
// Purpose: Initialize queue to empty.
// Returns: void
//--------------------------------------------
void InitQueue()
{
    head = tail = NULL;
}

//--------------------------------------------
// Function: ClearQueue()
// Purpose: Remove all items from the queue
// Returns: void
//--------------------------------------------
void ClearQueue()
{
    QNode *temp;
    while(head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }

    head = tail = NULL; // Reset indices to start over
}

//--------------------------------------------
// Function: Enqueue()
// Purpose: Enqueue an item into the queue.
// Returns: TRUE if enqueue was successful
//        or FALSE if the enqueue failed.
//--------------------------------------------
int Enqueue(char ch)
{
    QNode *temp;

    // Check to see if the Queue is full
    if(isFull()) return FALSE;

    // Create new node for the queue
    temp = (QNode *)malloc(sizeof(QNode));
    temp->ch = ch;
    temp->next = NULL;

    // Check for inserting first in the queue
    if(head == NULL)
        head = tail = temp;
    else
    {
        tail->next = temp; // Insert into the queue
        tail = temp;       // Set tail to new last node
    }

    return TRUE;
}

//--------------------------------------------
// Function: Dequeue()
// Purpose: Dequeue an item from the Queue.
// Returns: TRUE if dequeue was successful
//        or FALSE if the dequeue failed.
//--------------------------------------------
char Dequeue()
{
    char ch;
    QNode *temp;

    // Check for empty Queue
    if(isEmpty()) return '\0';  // Return null character if queue is empty
    else
    {
        ch = head->ch;        // Get character to return
        temp = head;
        head = head->next;    // Advance head pointer
        free(temp);            // Free old head
        // Check to see if queue is empty
        if(isEmpty())
        {
            head = tail = NULL;        // Reset everything to empty queue
        }
    }
    return ch;                // Return popped character
}

//--------------------------------------------
// Function: isEmpty()
// Purpose: Return true if the queue is empty
// Returns: TRUE if empty, otherwise FALSE
// Note: C has no boolean data type so we use
//    the defined int values for TRUE and FALSE
//    instead.
//--------------------------------------------
int isEmpty()
{
    return (head == NULL);
}

//--------------------------------------------
// Function: isFull()
// Purpose: Return true if the queue is full.
// Returns: TRUE if full, otherwise FALSE
//--------------------------------------------
int isFull()
{
    return FALSE;
}

int QueueSize()
{
    QNode *temp;
    temp = head;
    // Check for empty Queue
    while(temp!=NULL)
    {  
        temp = temp->next;
        count++;
    }
    return count;
}

// Shared queue
void InitQueue();

// Function declaration of all required functions
void* producerFun(void*);
void* add_B(void*);
void* add_C(void*);

// Getting the mutex , pthread_cond_signal() to wake up sleeping or waiting thread
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t dataNotProduced = PTHREAD_COND_INITIALIZER; //pthread_cond_wait() to wait or sleep
pthread_cond_t dataNotConsumed = PTHREAD_COND_INITIALIZER;

// Function to generate random numbers and
// push them into queue using thread A
void* producerFun(void *)
{
    static int producerCount = 0;
    // Initialising the seed
    srand(time(NULL));
    while(1)
    {
        // Getting the lock on queue using mutex
        pthread_mutex_lock(&mutex);
        if(QueueSize()<MAX && (producerCount<MAX))
        //if(producerCount<MAX)
        {
            // Getting the random number
            int num = rand() % 10 + 1;
            printf("Produced: %d ",num);
  
            // Pushing the number into queue
            Enqueue(num);

            producerCount++;
            pthread_cond_broadcast(&dataNotProduced);//to unblock all threads
        }
        // If queue is full, release the lock and return
        else if (producerCount == MAX) {
            pthread_mutex_unlock(&mutex);
            return NULL;
        }
        // If some other thread is exectuing, wait
        else {
            printf("Producer is in wait..");
            pthread_cond_wait(&dataNotConsumed, &mutex);
        }
        // Get the mutex unlocked
        pthread_mutex_unlock(&mutex);
    }
}

// Function definition for consumer thread 
void* add_B(void *)
{

    while (1)
    {   // Getting the lock on queue using mutex
        pthread_mutex_lock(&mutex);
  
        // Pop only when queue has at least 1 element
        if (QueueSize() > 0) 
        {
            // Get the data from the front of queue
            int data = (int) Dequeue();
  
            printf("B thread consumed: %d ",data);
  
            // Add the data to the integer variable
            // associated with thread B
            sum_B += data;
  
            // Pop the consumed data from queue
            // Dequeue();
  
            consumerCount1++;
  
            pthread_cond_signal(&dataNotConsumed);
        }
  
        // Check if consmed numbers from both threads
        // has reached to MAX value
        else if (consumerCount2 + consumerCount1 == MAX) {
            pthread_mutex_unlock(&mutex);
            return NULL;
        }
  
        // If some other thread is exectuing, wait
        else {
            printf("B is in wait..");
            pthread_cond_wait(&dataNotProduced, &mutex);
        }
  
        // Get the mutex unlocked
        pthread_mutex_unlock(&mutex);
    }
}

// Function definition for consumer thread C
void* add_C(void *)
{
    while (1) 
    {
  
        // Getting the lock on queue using mutex
        pthread_mutex_lock(&mutex);
  
        // Pop only when queue has at least 1 element
        if (QueueSize() != 0) 
        {
  
            // Get the data from the front of queue
            int data = (int)Dequeue();
            printf("C thread consumed: %d ",data);
  
            // Add the data to the integer variable
            // associated with thread B
            sum_C += data;
  
            // Pop the consumed data from queue
            // Dequeue();
            consumerCount2++;
  
            pthread_cond_signal(&dataNotConsumed);
        }
  
        // Check if consmed numbers from both threads
        // has reached to MAX value
        else if (consumerCount2 + consumerCount1 == MAX)
        {
            pthread_mutex_unlock(&mutex);
            return NULL;
        }
  
        // If some other thread is exectuing, wait
        else {
            printf("C is in wait..");
            // Wait on a condition
            pthread_cond_wait(&dataNotProduced, &mutex);
        }
  
        // Get the mutex unlocked
        pthread_mutex_unlock(&mutex);
    }
}

int main()
{
    // Declaring integers used to
    // identify the thread in the system
    pthread_t producerThread, consumerThread1, consumerThread2;

    // Function to create a threads
    // (pthread_create() takes 4 arguments)
    int retProducer = pthread_create(&producerThread, NULL, producerFun, NULL);
    int retConsumer1 = pthread_create(&consumerThread1, NULL, *add_B, NULL);
    int retConsumer2 = pthread_create(&consumerThread2, NULL, *add_C, NULL);

    // pthread_join suspends execution of the calling
    // thread until the target thread terminates
    if (!retProducer)
        pthread_join(producerThread, NULL);
    if (!retConsumer1)
        pthread_join(consumerThread1, NULL);
    if (!retConsumer2)
        pthread_join(consumerThread2, NULL);

    // Checking for the final value of thread
    if (sum_C > sum_B)
        printf("Winner is  Thread C");
    else if (sum_C < sum_B)
        printf("Winner is  Thread B");
    else
        printf("Both has same score");
      
    return 0;
}

