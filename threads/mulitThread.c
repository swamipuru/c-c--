#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <pthread.h>
#include<sched.h>

typedef enum { FALSE = 0, TRUE = 1 } Bool;
typedef Bool* BoolPtr;

int  NUMBER_OF_WORKER_THREADS =	10;

#define BOGUS 99

// Set one.
pthread_mutex_t StartWorkMutex;
pthread_cond_t StartWorkCondition;

Bool WorkOn = FALSE;
unsigned int Round = 0;

// Set two.
pthread_mutex_t CompleteMutex;
pthread_cond_t CompleteCondition;

Bool MainThreadWaiting = FALSE;
unsigned int TheCompletedBatch = BOGUS;

typedef struct student{
  long id;
  long range_a;
  long range_b;
  long res;
}student;
student *s;

void *WorkerThread(void *ThreadArgument){
  unsigned int X;
  long unsigned int ThisThreadNumber = (long unsigned int)ThreadArgument;

  int rc;
  int i;	
  pthread_key_t a_key;
  // Enter a waiting state for the "StartWorkCondition".
  pthread_mutex_lock(&StartWorkMutex);
  pthread_cond_wait(&StartWorkCondition, &StartWorkMutex);
  while ( TRUE ) {
    // It is necessary to unlock the "StartWorkMutex" before thread termination, so that the other worker threads can also terminate.
    sched_yield();
    if ( WorkOn ) {
      printf("Thread-%lu: Begin Work On Batch %d\n", ThisThreadNumber, Round);
    s = (student*)malloc(sizeof(student));
    rc = pthread_setspecific(a_key,s);    
 

 for(X=0;X<1;++X){
      s->id = rand()%10+1;
      s->range_a = rand()%10+1;
      s->range_b = rand()%10 + s->range_a;
      s->res = 0;
      //printf("student id: %ld, mod: %ld, range: a = %ld, b = %ld, res = %ld\n",s->id, s->id%3, s->range_a, s->range_b, s->res);
           
      //Sum
      if(s->id % 3 == 0){
	s->res = 0;
	for(i=s->range_a; i < s->range_b; ++i)
	  s->res = s->res+i;
	//	printf("thread: %lu res: %ld\n",ThisThreadNumber,s->res);
      }
      //product square
      if(s->id % 3 == 1){
	s->res = 1;
	for(i=s->range_a; i < s->range_b; ++i)
	  s->res = s->res*i*i;
	//	printf("thread: %lu res: %ld\n",ThisThreadNumber,s->res);
      }
      //multiply
      if(s->id % 3 == 2){
	s->res = 1;
	for(i=s->range_a; i<s->range_b; ++i)
	  s->res = s->res*i;
	// 	printf("thread: %lu res: %ld\n",ThisThreadNumber,s->res);
      }
      printf("thread:%lu student id: %ld, mod: %ld, range: a = %ld, b = %ld, res = %ld\n",ThisThreadNumber,s->id, s->id%3, s->range_a, s->range_b, s->res);
    
      free(s);
  }

 
     pthread_mutex_unlock(&StartWorkMutex);
    }
    else {
      pthread_mutex_unlock(&StartWorkMutex);
      pthread_exit(NULL);
    }

    while ( TRUE ) {
      pthread_mutex_lock(&CompleteMutex);

      if ( MainThreadWaiting == TRUE ) {
	  	MainThreadWaiting = FALSE;
	break;
      }
      pthread_mutex_unlock(&CompleteMutex);
    }
    TheCompletedBatch = ThisThreadNumber;
    //Lock the "StartWorkMutex" before we send out the "CompleteCondition" signal.
    pthread_mutex_lock(&StartWorkMutex);
    //printf("Thread-%lu: Completed Batch %d\n", ThisThreadNumber, Round);
    pthread_cond_signal(&CompleteCondition);
    pthread_mutex_unlock(&CompleteMutex);
    pthread_cond_wait(&StartWorkCondition, &StartWorkMutex);
  }
}

int main(int argc, char *argv[]){
  long unsigned int Identity;
  unsigned int X;
  unsigned int Y;
	
  // Initialize all of the thread related objects.
  pthread_t Threads[NUMBER_OF_WORKER_THREADS];
  pthread_attr_t attr;

  NUMBER_OF_WORKER_THREADS = atoi(argv[1]);
  printf("Number of worker threads:%d\n", NUMBER_OF_WORKER_THREADS);
	
  pthread_mutex_init(&CompleteMutex, NULL);
  pthread_cond_init (&CompleteCondition, NULL);
	
  pthread_mutex_init(&StartWorkMutex, NULL);
  pthread_cond_init (&StartWorkCondition, NULL);
	
  /* For portability, explicitly create threads in a joinable state */
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	
  // Create all of the worker threads here.
  for ( Identity = 0; Identity < NUMBER_OF_WORKER_THREADS; Identity++ ) pthread_create(&Threads[Identity], &attr, WorkerThread, (void *)Identity);

  printf("Wait for 1 second for the %d worker threads to enter a waiting state.\n\n", NUMBER_OF_WORKER_THREADS);
  //  sleep(1);
	
    // Lock the "StartWorkMutex" to set the global work coordination variables.
    pthread_mutex_lock(&StartWorkMutex);
    // Not a whole lot to coordinate in this framework demo.
    WorkOn = TRUE;
    printf("Main: Broadcast Signal To Start Batch| |\n");
    pthread_mutex_lock(&CompleteMutex);
    pthread_cond_broadcast(&StartWorkCondition);
    pthread_mutex_unlock(&StartWorkMutex);
		
    for ( Y = 0; Y < NUMBER_OF_WORKER_THREADS; Y++ ) {
      MainThreadWaiting = TRUE;
      pthread_cond_wait(&CompleteCondition, &CompleteMutex);
    }
    pthread_mutex_unlock(&CompleteMutex);
	
	
  pthread_mutex_lock(&StartWorkMutex);
  // Set the TERMINATION condition.
  WorkOn = FALSE;
  // printf("Main: Broadcast The Termination Signal\n");
  pthread_cond_broadcast(&StartWorkCondition);
  pthread_mutex_unlock(&StartWorkMutex);

  // Wait for all threads to complete, and then join with them.
  for ( X = 0; X < NUMBER_OF_WORKER_THREADS; X++ ) {
    pthread_join(Threads[X], NULL);
    // printf("Main: Thread[%d] Has Been Joined And Terminated.\n", X);
  }
	
  // Clean up and exit.
  pthread_attr_destroy(&attr);
  pthread_mutex_destroy(&CompleteMutex);
  pthread_cond_destroy(&CompleteCondition);
  pthread_mutex_destroy(&StartWorkMutex);
  pthread_cond_destroy(&StartWorkCondition);
  pthread_exit (NULL);
}
