#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX 10      // Maximum items to produce/consume
#define BUFLEN 10   // Size of the buffer
#define NUMTHREAD 2 // Number of threads

void *consumer(void *id);
void *producer(void *id);

char buffer[BUFLEN]; // Buffer for produced items
char source[] = "abcdef"; // Source of items to produce
int pCount = 0;      // Count of produced items
int cCount = 0;      // Count of consumed items

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t nonEmpty = PTHREAD_COND_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;

int main() {
    pthread_t thread[NUMTHREAD];
    // Create one producer and one consumer
    int thread_ids[NUMTHREAD] = {0, 1}; // Assign integer IDs for threads
    pthread_create(&thread[0], NULL, producer, (void *)&thread_ids[0]);
    pthread_create(&thread[1], NULL, consumer, (void *)&thread_ids[1]);

    // Wait for threads to finish
    for (int i = 0; i < NUMTHREAD; i++) {
        pthread_join(thread[i], NULL);
    }

    return 0;
}

void *producer(void *id) {
    int thread_id = *(int *)id; // Get the thread ID
    for (int i = 0; i < MAX; i++) {
        pthread_mutex_lock(&count_mutex);
        while (pCount >= BUFLEN) {
            pthread_cond_wait(&full, &count_mutex); // Wait if the buffer is full
        }
        // Produce an item
        buffer[pCount % BUFLEN] = source[pCount % strlen(source)];
        printf("%d produced %c by Thread %d\n", pCount, buffer[pCount % BUFLEN], thread_id);
        pCount++;
        pthread_cond_signal(&nonEmpty); // Signal the consumer
        pthread_mutex_unlock(&count_mutex);
        sleep(1); // Simulate work
    }
    return NULL;
}

void *consumer(void *id) {
    int thread_id = *(int *)id; // Get the thread ID
    for (int i = 0; i < MAX; i++) {
        pthread_mutex_lock(&count_mutex);
        while (cCount >= pCount) {
            pthread_cond_wait(&nonEmpty, &count_mutex); // Wait if the buffer is empty
        }
        // Consume an item
        char item = buffer[cCount % BUFLEN];
        printf("%d consumed %c by Thread %d\n", cCount, item, thread_id);
        cCount++;
        pthread_cond_signal(&full); // Signal the producer
        pthread_mutex_unlock(&count_mutex);
        sleep(1); // Simulate work
    }
    return NULL;
}

