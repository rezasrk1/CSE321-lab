#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5

pthread_mutex_t mutex;
int current_thread = 0;

void* thread_function(void* arg) {
    int thread_id = *((int*)arg);
    
    // Wait until it's this thread's turn
    pthread_mutex_lock(&mutex);
    while (current_thread != thread_id) {
        pthread_mutex_unlock(&mutex);
        sched_yield(); // Yield to allow other threads to run
        pthread_mutex_lock(&mutex);
    }

    // Print running status
    printf("thread-%d running\n", thread_id + 1);
    sleep(1); // Simulate some work being done

    // Print closed status
    printf("thread-%d closed\n", thread_id + 1);
    
    // Update to next thread
    current_thread++;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i; // Pass thread ID
        pthread_create(&threads[i], NULL, thread_function, (void*)&thread_ids[i]);
    }

    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy mutex
    pthread_mutex_destroy(&mutex);
    return 0;
}

