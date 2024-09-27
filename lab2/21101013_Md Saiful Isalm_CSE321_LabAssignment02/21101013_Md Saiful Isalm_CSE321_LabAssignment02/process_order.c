#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid, grandchild_pid;

    child_pid = fork();

    if (child_pid < 0) {
        
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {

        grandchild_pid = fork();

        if (grandchild_pid < 0) {
            
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (grandchild_pid == 0) {

            printf("I am grandchild\n");
            exit(EXIT_SUCCESS);   
            wait(NULL);  
            printf("I am child\n");
            exit(EXIT_SUCCESS);  
        }
    } else {
        wait(NULL); 
        printf("I am parent\n");
    }

    return 0;
}

