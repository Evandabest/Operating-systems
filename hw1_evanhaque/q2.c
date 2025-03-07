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

int search (char* file, char* dir);

int main() {

    search("output.txt", "lab1");
    
    return 0;
}

int search (char* file, char* dir) {
    DIR *dirptr=opendir(dir);
    char directory[256];
    if (getcwd(directory, 256) == NULL) {
        perror("Error getting current working directory");
        printf("Errno: %d\n", errno);
        exit(1);
    }
    else if (getcwd(directory, 256) == dir) {
        printf("Current working directory is %s\n", directory);
    }
    else {
        if (chdir(dir) != 0) {
            perror("Error changing directory");
            printf("Errno: %d\n", errno);
            exit(1);
        }
        else {
            printf("Changed working directory to %s\n", dir);
        }
    }
    struct dirent *entry = readdir(dirptr);
    struct stat statbuf;
    while (entry != NULL) {
        if (strlen(entry->d_name) == strlen(file) && (strcmp(entry->d_name, file) == 0)) {
            stat(entry->d_name, &statbuf);
            printf("File %s found in directory %s\nThe size of the file is %lld bytes", entry->d_name, dir, (long long)statbuf.st_size);
            entry = readdir(dirptr);
            closedir(dirptr);
            return 0; /* return success */
        }
        entry = readdir(dirptr);
    };  

    closedir(dirptr);
    printf("File not found\n");
    return 1; /* return failure */
};
