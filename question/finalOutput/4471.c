#include <pthread.h>	/* pthread functions and data structures 	*/
#include <stdio.h>		/* standard I/O routines				 	*/
#include <sys/time.h>   /* gettimeofday()							*/
#include<limits.h>
#include<stdlib.h>
/*	global mutex for my program. assignment initializes it	*/
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/*	global variable - numthreads - an integer value that specifies how many threads will be created	*/
int numthreads;
/*	global variable - increment - the number of integer values that each thread will work with	*/
int increment;

/*	global variable - id indicates which thread is, startInt indicates the first number for each thread working on	*/
struct parameter
{
	int id;
	int startInt;
};

typedef struct node{
  int id;
  struct node *next;
}node;
node *head;

void insert(int id){
  node *ptr,*temp;
  if(head == NULL){
    head = (node*)malloc(sizeof(node));
    head->id = id;
    head->next = NULL;
  }else{
    ptr = head;
    while(ptr->next != NULL){
      ptr = ptr->next;
    }
    temp = (node*)malloc(sizeof(node));
    temp->id = id;
    temp->next;
    ptr->next = temp;
  }
}

void traverse(){
  node *ptr = head;
  while(ptr != NULL){
    printf("%d ",ptr->id);
    ptr = ptr->next;
  }
  printf("\n");
  free(ptr);
}

/*	function sum() - calculate the sum of the array
	algorithm - get the first number of 1 thread, and add increment times
	input - the first number of each thread
	output - the sum of the array	*/
int sum(int a)
{
	int sum = 0;
	int i;			/* loop counter	*/
	for (i = 0; i < increment; i++)
	{
		sum += a++;
	}
	return sum;
}

/*	function to be executed by the new thread	*/
/*	function do_loop() - calculate the sum of the array, and calculate the time cost as well
	algorithm - get id and startInt of 1 thread, calculate the sum of the array and the time cost 
    input - id of thread, startInt of thread
    output - none	*/
void* do_loop(void* data)
{	
/*	clock_t start, end;
	start = clock();*/
	struct timeval tv1, tv2;
	gettimeofday(&tv1, NULL);					/* record the beginning time of the thread	*/
	int rc = pthread_mutex_lock(&mutex);		/* lock the mutex	*/
	if (rc)
	{
		perror("pthread_mutex_lock");
		pthread_exit(NULL);
	}
	struct parameter *pa = (struct parameter*) data;	/* pointer to a parameter	*/
	if(pa == NULL){

	}else{
	  int s = sum(pa -> startInt);						/* calculate the sum of the array	*/
	if(s<=0|| s > INT_MAX){
	  insert(pa->id);
	}

	  printf("start interval : %d, thread id : %d, sum : %d\n", pa -> startInt, pa -> id, s);
	  /*	change the first number of thread for next thread	*/
	  pa -> startInt +=increment;			/* change the startInt for next thread	*/
	  pthread_mutex_unlock(&mutex);		/* unlock mutex		*/
	  /*	end = clock();
		double duration = 1000000 * (end - start) / CLOCKS_PER_SEC;*/
	  gettimeofday(&tv2, NULL);					/* record the finishing time	*/
	  long duration = 1000000 * (tv2.tv_sec - tv1.tv_sec) + (tv2.tv_usec - tv1.tv_usec);		/* calculate the time cost of the thread	*/
	  printf("run duration : %ld microseconds\n", duration);
	  /* terminate the thread */
	  pthread_exit(NULL);		
	  free(pa);
	}	
}

int isDigit(char *str){
  int i=0;
  int rt = 1;
  while(str[i]){
    if(str[i] < 48 || str[i] > 57){
      rt = 0;
      break;
    }
    i++;
  }
  return rt;
}

/* like any C program, program's execution begins in main */
int main(int argc, char **argv)
{
/*	clock_t start, end;
	start = clock();*/
  if(argc < 3){
    printf("System expecting more number of inputs.\n");
    printf("Please enter num_of_threads and interval values as command line arguments!!!\n");
  }else if(isDigit(argv[1])==0 || isDigit(argv[2])==0){
    printf("System expecting some number input!!!!\n");
  }else{
        struct timeval tv1, tv2;
	gettimeofday(&tv1, NULL);			/* record the beginning time of the program	*/
	const int firstint = 0;				/* const variable firstint for initializes the program	*/
	numthreads = atoi(argv[1]);			/* assigned to numthreads	*/
	increment = atoi(argv[2]);			/* assigned to increment	*/
	struct parameter new;				
	new.startInt = firstint;			/* initializes the startInt	*/
	pthread_t p_thread;

/*	create the number of numthreads threads	*/	
	int j;
	for (j = 0; j < numthreads; j++)
	{
		new.id = j;
		pthread_create(&p_thread, NULL, do_loop, (void*)&new);
		pthread_join(p_thread, NULL);
	}
/*	end = clock();
	double duration = 1000000 * (end - start) / CLOCKS_PER_SEC;*/
	gettimeofday(&tv2, NULL);			/* record the finishing time of the program	*/
	long duration = 1000000 * (tv2.tv_sec - tv1.tv_sec) + (tv2.tv_usec - tv1.tv_usec);		/* calculate the time cost of the program	*/
	printf("Program run duration was : %ld microseconds\n", duration);
	if(head != NULL)
	  printf("\nList of threads not supported::\n");
	traverse();
  }
	return 0;
} 
