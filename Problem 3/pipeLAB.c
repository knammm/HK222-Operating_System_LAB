#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int pfd1[2], pfd2[2];
// pfd1 : parent to child    // write(Parent) >====< read(Child)  Parent -> Child
// pfd2 : child to parent    // write(Child)  >====< read(Parent) Child -> Parent

void INIT(void) {
	if (pipe(pfd1) < 0 || pipe(pfd2) < 0) {
		perror("pipe error !");
		exit(EXIT_FAILURE);
	}

}
void WRITE_TO_PARENT(void) {
	/*send parent a message through pipe*/
	// TO DO
	char message[256];
	sprintf(message, "Child send Parent a message !");
	write(pfd2[1], message, sizeof(message));
	printf("Child send message to parent!\n");
	printf("===============================\n");

}
void READ_FROM_PARENT(void) {
	/* read message sent by parent from pipe */
	// TO DO
	char message[256];
	read(pfd1[0], message, sizeof(message));
	printf("Child has received message from parent: %s\n", message);
	printf("===============================\n");
}
void WRITE_TO_CHILD(void) {
	/* send child a message through pipe */
	// TO DO
	char message[256];
	sprintf(message, "Parent send Child a message !");
	write(pfd1[1], message, sizeof(message));
	printf("Parent send message to child !\n");
	printf("===============================\n");
}
void READ_FROM_CHILD(void) {
	/* read the message sent by child from pipe */
	// TO DO
	char message[256];
	read(pfd2[0], message, sizeof(message));
	printf("Parent has received message from child: %s\n", message);
	printf("===============================\n");
}

int main(int argc, char* argv[]) {
	INIT();
	pid_t pid;
	pid = fork();
	// set a timer, process will end after 10 seconds.
	alarm(10);
	if (pid == 0) {
		while (1) {
			sleep(rand() % 2 + 1);
			WRITE_TO_CHILD();
			READ_FROM_CHILD();
		}
	}
	else {
		while (1) {
			sleep(rand() % 2 + 1);
			READ_FROM_PARENT();
			WRITE_TO_PARENT();
		}
	}
	return 0;
}


