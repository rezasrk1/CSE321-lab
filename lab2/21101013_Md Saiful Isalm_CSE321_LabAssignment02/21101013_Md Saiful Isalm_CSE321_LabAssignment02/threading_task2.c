#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5
#define NUM_PRINTS 5

// Structure to hold thread arguments
typedef struct {
    int thread_id;
    int start_value;
} thread_data_t;

// Thread function to print integers
void* print_numbers(void* arg) {
    thread_data_t* data = (thread_data_t*)arg;
    int thread_id = data->thread_id;
    int start_value = data->start_value;

    for (int i = 0; i < NUM_PRINTS; i++) {
        printf("Thread %d prints %d\n", thread_id, start_value + i);
    }
    
    free(arg); // Free the allocated memory for thread data
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data_t* data = malloc(sizeof(thread_data_t));
        data->thread_id = i;
        data->start_value = i * NUM_PRINTS + 1; // Calculate starting value for each thread

        pthread_create(&threads[i], NULL, print_numbers, (void*)data);
    }

    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

