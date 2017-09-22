#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* thread (void* vargp);

typedef struct
{
	int T;  //unique number held by each thread
	int maxT;  //max number that CAN be held by a thread
}numSet;

int main (int argc, char** argv)
{
	pthread_t* tid1; //initializing the pointers for tid and thread arguments
	pthread_t* tid2;  
	numSet* arg1;
	numSet* arg2;
	int N = atoi(argv[1]); //store the command line argument

	if((1 << N) - 2 == 0) //taking care the case that N = 1, when main thread would be the only leaf thread
	{
		printf("Thread %d done\n", 0);
	}

	//allocating space for all these pointers
	tid1 = malloc(sizeof(pthread_t));
	tid2 = malloc(sizeof(pthread_t));
	arg1 = malloc(sizeof(numSet));
	arg2 = malloc(sizeof(numSet));

	//initializing the structures, prepare for being passed in as thread arguments
	arg1->T = 1;
	arg1->maxT = (1 << N) - 2;
	arg2->T = 2;
	arg2->maxT = (1 << N) - 2;

	pthread_create(tid1, NULL, thread, (void*)arg1);
	pthread_create(tid2, NULL, thread, (void*)arg2);

	pthread_join(*tid1, NULL);
	pthread_join(*tid2, NULL);

	//free the all the pointers that we performed malloc on, prevent mem leak
	free(tid1);
	free(tid2);
	free(arg1);
	free(arg2);

	//print exit message
	printf("Thread %d done\n", 0);
	exit(0);
}

void* thread (void* vargp)
{
	pthread_t* tid1;
	pthread_t* tid2;
	numSet* arg1;
	numSet* arg2;
	numSet* threadSet = (numSet*)vargp;
	int T = threadSet->T;

	if(2 * T + 1 > threadSet->maxT) //taking care of leaf threads
	{
		printf("Thread %d done\n", T);
		return NULL;
	}

	tid1 = malloc(sizeof(pthread_t));
	tid2 = malloc(sizeof(pthread_t));
	arg1 = malloc(sizeof(numSet));
	arg2 = malloc(sizeof(numSet));

	arg1->T = 2 * T + 1;
	arg1->maxT = threadSet->maxT;
	arg2->T = 2 * T + 2;
	arg2->maxT = threadSet->maxT;

	pthread_create(tid1, NULL, thread, (void*)arg1);
	pthread_create(tid2, NULL, thread, (void*)arg2);

	pthread_join(*tid1, NULL);
	pthread_join(*tid2, NULL);

	free(tid1);
	free(tid2);
	free(arg1);
	free(arg2);

	printf("Thread %d done\n", T);
}