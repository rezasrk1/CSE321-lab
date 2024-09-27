#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    pid_t a;
    pid_t b;
    pid_t c;

    int process_counter = 1;

    a = fork();
    b = fork();
    c = fork();

    if (a != 0) {
        process_counter++;
    } 
    else {
        if (a % 2 != 0) {
            process_counter++;
            fork();
        }
    }

    if (b != 0) {
        process_counter++;
    } 
    else {
        if (b % 2 != 0) {
            process_counter++;
            fork();
        }
    }

    if (c != 0) {
        process_counter++;
    } 
    else {
        if (c % 2 != 0) {
            process_counter++;
            fork();
        }
    }

    while (wait(NULL) > 0);

    if (a > 0 && b > 0 && c > 0) {
        printf("Value of a: %d\n", a);
        printf("Value of b: %d\n", b);
        printf("Value of c: %d\n", c);
        printf("Total number of processes created: %d\n", process_counter);
    }
}
