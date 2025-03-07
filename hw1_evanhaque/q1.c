#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/dir.h>

void question1();

int main() {

    question1();
    
    return 0;
}

void question1() {
    // make a directory named lab 1
    const char *name = "lab1";
    int status = mkdir(name, 0755);

    if (status == 0) {
        printf("Directory '%s' created successfully.\n", name);
    }
    else {
        perror("Error creating directory");
        printf("Errno: %d\n", errno);
    }

    int fd, sz;
    char* c = (char*)calloc(100, sizeof(char));
    fd = open("source.txt", O_RDONLY);
    if (fd < 0) {
        perror("r1");
        exit(1);
    }


    if (chdir(name) != 0) {
        perror("Error changing directory");
        printf("Errno: %d\n", errno);
        exit(1);
    } else {
        printf("Changed working directory to %s\n", name);
    }

    int fdescript;
    char *filename = "output.txt";
    fdescript =  creat(filename, S_IRWXU);

    char* buff = (char*)calloc(1, sizeof(char));

    int count = 0;
    while ((sz = read(fd, buff, 1)) > 0) {
        if (buff[0] == '1' && isalnum(buff[0])) {
            buff[0] = 'A';
        }

        sz = write(fdescript, buff, 1);
        count++;

        if (count == 100) {
            sz = write(fdescript, "XYZ", 3);
            count = 0;
        }

    }

    if (close(fd) < 0) {
        perror("c1");
        exit(1);
    }
    printf("closed the fd.\n");

    if (close(fdescript) < 0) {
        perror("c1");
        exit(1);
    }
    printf("closed the fdescript.\n");

    if (chdir("..") != 0) {
        perror("Error changing directory");
        printf("Errno: %d\n", errno);
        exit(1);
    } else {
        printf("Changed working directory to parent directory\n");
    }
}

