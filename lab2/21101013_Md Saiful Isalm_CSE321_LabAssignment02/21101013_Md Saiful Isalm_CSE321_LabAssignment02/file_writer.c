#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int fd;
    char filename[256];
    char buffer[BUFFER_SIZE];

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    snprintf(filename, sizeof(filename), "%s", argv[1]);

    fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd < 0) {
        perror("Error opening/creating file");
        exit(EXIT_FAILURE);
    }

    printf("Enter strings to write to the file (type '-1' to stop):\n");

    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            perror("Error reading input");
            close(fd);
            exit(EXIT_FAILURE);
        }

        buffer[strcspn(buffer, "\n")] = 0;

        if (strcmp(buffer, "-1") == 0) {
            break;
        }

        if (write(fd, buffer, strlen(buffer)) < 0) {
            perror("Error writing to file");
            close(fd);
            exit(EXIT_FAILURE);
        }

        if (write(fd, "\n", 1) < 0) {
            perror("Error writing newline to file");
            close(fd);
            exit(EXIT_FAILURE);
        }
    }

    close(fd);

    printf("Finished writing to the file.\n");

    return 0;
}

