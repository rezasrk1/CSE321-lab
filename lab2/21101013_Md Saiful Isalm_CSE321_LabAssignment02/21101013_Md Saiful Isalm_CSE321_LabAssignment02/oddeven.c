#include <stdio.h>
#include <stdlib.h>

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

    checkOddEven(arr, n);
    
    free(arr);
    return 0;
}

