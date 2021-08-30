#include <stdio.h>  
#include <string.h>  
#include <pthread.h>  

// Global variable:  
int i = 2;  

void* foo(void* p) 
{  
  // Print value received as argument:
  printf("Value recevied as argument in routine: ");  
  printf("%i\n", * (int*)p); 
}  

int sum(int *a, int *b) 
{
    printf("\nUsage of values residing in the address space after termination %d+%d = %d\n", *a, *b, *a+*b);
} 

int main(void) 
{  
  // Declare variable for thread's ID:
  pthread_t id1, id2; 
  int j = 1; 
  int k = 3; 
  int *ptr; 

  pthread_create(&id1, NULL, foo, &j);  
  printf("\nID1: %lu \n", id1);  
  pthread_create(&id2, NULL, foo, &k);  
  pthread_join(id1, (void**)&ptr); 
  printf("\nID2: %lu \n", id2); 

  sum(&j, &k); 
// Return reference to global variable:  
  pthread_exit(&i);  
}  