#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#define MAX_LEN 512
#define READ 0
#define WRITE 1

int main(int argc, char* argv[]) {

    if(argc != 2) {
        printf("Usage: ./p3a <file_name>\n");
        exit(1);
    }

    int fd[2],n;
    char buffer[MAX_LEN];
    pid_t pid;
    pipe(fd);
    pid = fork();
    if(pid > 0) {
        close(fd[READ]);
        dup2(fd[WRITE],STDOUT_FILENO);
        execlp("cat","cat",argv[1],NULL);
        printf("Failed to exec()!\n");
        exit(1);
    }
    else {
        close(fd[WRITE]);
        dup2(fd[READ],STDIN_FILENO);
        execlp("sort","sort",NULL);
        printf("Failed to exec()!\n");
        exit(1);
    }
    return 0;
}