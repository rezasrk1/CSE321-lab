#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void sortDescending(int arr[], int n) {
    int temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] < arr[j]) { // Sort in descending order
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void checkOddEven(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            printf("%d is even\n", arr[i]);
        } else {
            printf("%d is odd\n", arr[i]);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <numbers>\n", argv[0]);
        return 1;
    }

    int n = argc - 1;
    int *arr = malloc(n * sizeof(int));

    for (int i = 1; i < argc; i++) {
        arr[i - 1] = atoi(argv[i]); // Convert arguments to integers
    }

    pid_t pid = fork(); // Create a child process

    if (pid < 0) {
        perror("Fork failed");
        free(arr);
        return 1;
    } else if (pid == 0) {
        // Child process
        sortDescending(arr, n);
        printf("Sorted array in descending order from child process:\n");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        exit(0); // Exit child process
    } else {
        // Parent process
        wait(NULL); // Wait for the child to finish
        checkOddEven(arr, n);
    }

    free(arr);
    return 0;
}

