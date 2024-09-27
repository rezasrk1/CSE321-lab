#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t a, b, c, d;
    int counter = 1;

    a = fork(); // Create first child process
    if (a == 0) {
        // Child process
        printf("%d. Child process ID: %d\n", counter++, getpid());

        b = fork(); // Create first grandchild
        if (b == 0) {
            printf("%d. Grand Child process ID: %d\n", counter++, getpid());
            return 0;
        }

        c = fork(); // Create second grandchild
        if (c == 0) {
            printf("%d. Grand Child process ID: %d\n", counter++, getpid());
            return 0;
        }

        d = fork(); // Create third grandchild
        if (d == 0) {
            printf("%d. Grand Child process ID: %d\n", counter++, getpid());
            return 0;
        }

        // Wait for all grandchildren to finish
        wait(NULL);
        wait(NULL);
        wait(NULL);
    } else {
        // Parent process
        printf("%d. Parent process ID: %d\n", counter, getpid());
        wait(NULL); // Wait for the first child to finish
    }

    return 0;
}

