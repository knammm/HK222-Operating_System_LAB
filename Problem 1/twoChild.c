#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#define SHM_KEY 0x696
#define numMovies 1682


typedef struct {
    int numberOfRatings;
    int sumOfRatings;
}movies;


void readFile(char* filename, movies* data) {
    FILE* fptr = fopen(filename, "r");
    char line[512];
    while (fgets(line, sizeof(line), fptr) != NULL) {
        int movieID, movieRating;
        char* token = strtok(line, "\t");
        token = strtok(NULL, "\t");
        movieID = atoi(token);
        token = strtok(NULL, "\t");
        movieRating = atoi(token);
        data[movieID].numberOfRatings += 1;
        data[movieID].sumOfRatings += movieRating;
    }
    fclose(fptr);
}
int main() {
    int shmid;
    movies* data;
    shmid = shmget(SHM_KEY, sizeof(data) * numMovies, 0644 | IPC_CREAT);
    if (shmid < 0) {
        perror("shmget");
        return 1;
    }
    data = (movies*)shmat(shmid, NULL, 0);
    memset(data, 0, sizeof(data) * numMovies);
    if (data == (movies*)-1) {
        perror("shmat");
        exit(1);
    }
    pid_t pid1 = fork();
    // FIRST CHILD
    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid1 == 0) {
        readFile("/home/knam/movie-100k_1.txt", data);
    }
    pid_t pid2 = fork();
    // SECOND CHILD
    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid2 == 0) {
        readFile("/home/knam/movie-100k_2.txt", data);
    }
    // Waiting 2 child process
    // This is parent process place
    int processStatus;
    waitpid(pid1, &processStatus, 0);
    waitpid(pid2, &processStatus, 0);
    float average;
    int sumAll = 0;
    printf("Movie ID\tAverage Rating\n");
    for (int i = 1; i < numMovies; i++) {
        average = (float)data[i].sumOfRatings / (float)data[i].numberOfRatings;
        printf("%d\t\t%f\n", i, average);
    }
    return 0;
}
