#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Usage: %s source.txt destination.txt\n", argv[0]);
        return 1;
    }

    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    pid_t pid[4];

    
    for (int i = 0; i < 4; i++) {
        pid[i] = fork();
        
        if (pid[i] < 0) {
            perror("Fork failed");
            return 1;
        } else if (pid[i] == 0) {
            if (i == 0) {

                execl("./child1", "child1", argv[1], argv[2], NULL);
                perror("Exec failed for child1");
                exit(1);
            } else if (i == 1) {

                close(pipe_fd[0]); 
                int rand_num1 = rand() % 11; 
                printf("Child 2: Generated random number: %d\n", rand_num1);
                write(pipe_fd[1], &rand_num1, sizeof(rand_num1));
                close(pipe_fd[1]);
                exit(0);
            } else if (i == 2) {
                srand(time(NULL));
                close(pipe_fd[0]); 
                int rand_num2 = rand() % 11; 
                printf("Child 3: Generated random number: %d\n", rand_num2);
                write(pipe_fd[1], &rand_num2, sizeof(rand_num2));
                close(pipe_fd[1]);
                exit(0);
            } else if (i == 3) {
                srand(time(NULL));
                execl("/bin/date", "date", NULL);
                perror("Exec failed for date");
                exit(1);
            }
        } else if (i != 0) {
            continue;
        }
    }
    
    close(pipe_fd[1]); 
    
    waitpid(pid[1], NULL, 0);
    int rand_num1;
    read(pipe_fd[0], &rand_num1, sizeof(rand_num1));
    printf("Parent: Received random number from Child 2: %d\n", rand_num1);
    
    waitpid(pid[2], NULL, 0);
    int rand_num2;
    read(pipe_fd[0], &rand_num2, sizeof(rand_num2));
    printf("Parent: Received random number from Child 3: %d\n", rand_num2);
    
    if (rand_num1 > rand_num2) {
        printf("Winner: Child 2 with random number %d\n", rand_num1);
    } else if (rand_num2 > rand_num1) {
        printf("Winner: Child 3 with random number %d\n", rand_num2);
    } else {
        printf("It's a tie between Child 2 and Child 3 with number %d\n", rand_num1);
    }
    
    close(pipe_fd[0]);
    
    printf("Waiting for Child 4 to print the date...\n");
    waitpid(pid[3], NULL, 0);
    
    return 0;
}