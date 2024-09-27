#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_CROPS 5 // Maximum crops a Farmer can produce or a ShopOwner can take
#define WAREHOUSE_SIZE 5 // Size of the warehouse

sem_t empty; // Semaphore to count empty slots in the warehouse
sem_t full;  // Semaphore to count filled slots in the warehouse
pthread_mutex_t mutex; // Mutex for critical section

char crops[WAREHOUSE_SIZE] = {'N', 'N', 'N', 'N', 'N'}; // Warehouse initialized to empty

void *Farmer(void *farmer_id) {
    int id = *((int *)farmer_id);
    char crop_types[5] = {'R', 'W', 'P', 'S', 'M'}; // Different crop types

    for (int i = 0; i < MAX_CROPS; i++) {
        sem_wait(&empty); // Wait for an empty slot in the warehouse
        pthread_mutex_lock(&mutex); // Enter critical section

        // Determine the crop type and room to fill
        int room = id % WAREHOUSE_SIZE;
        crops[room] = crop_types[id % 5]; // Assign crop type based on farmer ID
        printf("Farmer %d: Insert crops %c at %d\n", id, crops[room], room);

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&full); // Signal that a crop has been added

        sleep(1); // Simulate time taken to produce crops
    }
    return NULL;
}

void *ShopOwner(void *shop_owner_id) {
    int id = *((int *)shop_owner_id);

    for (int i = 0; i < MAX_CROPS; i++) {
        sem_wait(&full); // Wait for a filled slot in the warehouse
        pthread_mutex_lock(&mutex); // Enter critical section

        // Determine which crop to remove
        int room = id % WAREHOUSE_SIZE;
        char crop = crops[room];
        crops[room] = 'N'; // Mark room as empty
        printf("Shop Owner %d: Remove crops %c from %d\n", id, crop, room);

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&empty); // Signal that a crop has been removed

        sleep(1); // Simulate time taken to take crops
    }
    return NULL;
}

int main() {
    pthread_t farmers[5], shop_owners[5];
    int farmer_ids[5] = {0, 1, 2, 3, 4};
    int shop_owner_ids[5] = {0, 1, 2, 3, 4};

    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, WAREHOUSE_SIZE); // Initialize with full capacity
    sem_init(&full, 0, 0); // Initialize with 0 crops

    // Create threads for farmers
    for (int i = 0; i < 5; i++) {
        pthread_create(&farmers[i], NULL, Farmer, (void *)&farmer_ids[i]);
    }

    // Create threads for shop owners
    for (int i = 0; i < 5; i++) {
        pthread_create(&shop_owners[i], NULL, ShopOwner, (void *)&shop_owner_ids[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 5; i++) {
        pthread_join(farmers[i], NULL);
        pthread_join(shop_owners[i], NULL);
    }

    // Cleanup
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}

