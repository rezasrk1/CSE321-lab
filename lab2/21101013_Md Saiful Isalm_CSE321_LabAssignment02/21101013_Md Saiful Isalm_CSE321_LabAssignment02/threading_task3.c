#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

int *value; 
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int asciiMake(char *string) {
    int calculate = 0;
    int counter = 0;

    while(string[counter] != '\0') {
        calculate += string[counter];
        counter++;
    }
    return calculate;
}

void *threadCreate(void *arg){
    char string[999];
    int add;
    
    pthread_mutex_lock(&mutex);
    printf("Enter Your Name: \n");
    scanf("%s", string);
    pthread_mutex_unlock(&mutex);

    add = asciiMake(string);

    pthread_exit((void*)(intptr_t)add);
}

int main() {
    pthread_t array[3];
    int val[3];
    int j = 0;
    
    for (int i = 0; i < 3; i++){
        pthread_create(&array[i], NULL, threadCreate, NULL);
    }

    for (int i = 0; i < 3; i++){
        pthread_join(array[i], (void**)&value);
        val[j] = (int)(intptr_t)value;
        j++;
    }

    // Checking the logic
    int flag = 0;

    if (val[0] == val[1] && val[0] == val[2] && val[1] == val[2]) {
        flag = 1;
    }
    else if (val[0] == val[1] || val[0] == val[2] || val[1] == val[2]) {
        flag = 2;
    }
    else {
        flag = 3;
    }

    // Printing the result
    if (flag == 1) {
        printf("Youreka\n");
    }
    else if (flag == 2) {
        printf("Miracle\n");
    }
    else if (flag == 3) {
        printf("Hasta la vista\n");
    }

    pthread_mutex_destroy(&mutex);
}
