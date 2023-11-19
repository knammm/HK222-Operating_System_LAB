#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]) {
	// Time consuming
	clock_t start, end;
	double execution_time;
	start = clock();
	
	// Wrong condition
	if (argc != 2) {
		printf("Wrong command. Please use ./sum_serial n\n");
		return 0;
	}
	
	// Declare variables
	int n = atoi(argv[1]);
	long long sum = 0;
	
	// Calculate sum
	for (int i = 0; i <= n; i++) {
		sum += i;
	}
	printf("Sum from 1 to %d is %lld\n", n, sum);
	
	// Time consuming
	end = clock();
	execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
	printf("Time taken to execute in seconds : %f\n", execution_time);
	return 0;
	
}
