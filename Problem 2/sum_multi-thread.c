#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
	int startPoint;
	int endPoint;
	long long sumResult;
}argument;

void *calculate_sum_Thread(void* arg){
	argument* processThread = (argument*)arg;
	long long sum = 0;
	for(int i = processThread->startPoint; i <= processThread->endPoint; i++){
		sum += i;
	}
	processThread->sumResult = sum; // result is stored
	pthread_exit(NULL);
}

int main(int arg, char* argv[]){
	// Time consuming
	clock_t start, end;
	double execution_time;
	start = clock();
	
	// Wrong condition
	if(arg != 3){
		printf("Wrong command ! Please enter again\n");
		return 1;
	}
	
	// Declare variables
	int numOfThreads = atoi(argv[1]);
	int n = atoi(argv[2]);
	pthread_t threads[numOfThreads];
	argument arguments[numOfThreads];
	
	for(int i = 0; i < numOfThreads; i++){
		// Getting interval
		arguments[i].startPoint = ((i * n) / numOfThreads) + 1;
		arguments[i].endPoint = ((i + 1) * n) / numOfThreads;
		// Creating threads
		pthread_create(&threads[i], NULL, calculate_sum_Thread, &arguments[i]);
	}
	
	// Getting result
	long long result = 0;
	for(int i = 0; i < numOfThreads; i++){
		pthread_join(threads[i], NULL);
		result += arguments[i].sumResult;
	}
	
	printf("Sum from 1 to %d is : %lld\n", n, result);
	
	// Time consuming
	end = clock();
	execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
	printf("Time taken to execute in seconds : %f\n", execution_time);
	return 0;
}
