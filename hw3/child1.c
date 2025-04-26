#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s source.txt destination.txt\n", argv[0]);
        return 1;
    }
    
    int source_fd = open(argv[1], O_RDONLY);
    if (source_fd < 0) {
        perror("Error opening source file");
        printf("Errno: %d\n", errno);
        return 1;
    }
    
    int dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0) {
        perror("Error opening destination file");
        printf("Errno: %d\n", errno);
        close(source_fd);
        return 1;
    }
    
    char* buff = (char*)calloc(1, sizeof(char));
    if (buff == NULL) {
        perror("Memory allocation failed");
        close(source_fd);
        close(dest_fd);
        return 1;
    }
    

    ssize_t sz;
    int count = 0;
    
    while ((sz = read(source_fd, buff, 1)) > 0) {
        
        sz = write(dest_fd, buff, 1);
        if (sz != 1) {
            perror("Write error");
            printf("Errno: %d\n", errno);
            free(buff);
            close(source_fd);
            close(dest_fd);
            return 1;
        }
        
        count++;
    }
    
    if (sz < 0) {
        perror("Read error");
        printf("Errno: %d\n", errno);
        free(buff);
        close(source_fd);
        close(dest_fd);
        return 1;
    }
    
    printf("Child 1: Successfully copied content from %s to %s\n", argv[1], argv[2]);
    

    free(buff);
    
    if (close(source_fd) < 0) {
        perror("Error closing source file");
        printf("Errno: %d\n", errno);
        return 1;
    }
    printf("Closed the source file.\n");
    
    if (close(dest_fd) < 0) {
        perror("Error closing destination file");
        printf("Errno: %d\n", errno);
        return 1;
    }
    printf("Closed the destination file.\n");
    
    return 0;
}