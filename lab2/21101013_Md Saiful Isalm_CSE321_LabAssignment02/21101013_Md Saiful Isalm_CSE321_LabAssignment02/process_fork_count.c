#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t a, b, c, new_child_pid;
    int process_count = 1;

    a = fork();
    if (a < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (a == 0) {
        process_count++;
        if (getpid() % 2 != 0) {
            new_child_pid = fork();
            if (new_child_pid < 0) {
                perror("fork");
                exit(EXIT_FAILURE);
            }
            if (new_child_pid == 0) {
                process_count++;
                exit(EXIT_SUCCESS);
            }
        }
        wait(NULL);
        exit(EXIT_SUCCESS);
    }

    b = fork();
    if (b < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (b == 0) {
        process_count++;
        if (getpid() % 2 != 0) {
            new_child_pid = fork();
            if (new_child_pid < 0) {
                perror("fork");
                exit(EXIT_FAILURE);
            }
            if (new_child_pid == 0) {
                process_count++;
                exit(EXIT_SUCCESS);
            }
        }
        wait(NULL);
        exit(EXIT_SUCCESS);
    }

    c = fork();
    if (c < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (c == 0) {
        process_count++;
        if (getpid() % 2 != 0) {
            new_child_pid = fork();
            if (new_child_pid < 0) {
                perror("fork");
                exit(EXIT_FAILURE);
            }
            if (new_child_pid == 0) {
                process_count++;
                exit(EXIT_SUCCESS);
            }
        }
        wait(NULL);
        exit(EXIT_SUCCESS);
    }

    wait(NULL);
    wait(NULL);
    wait(NULL);

    printf("Total processes created including the initial parent: %d\n", process_count);

    return 0;
}

