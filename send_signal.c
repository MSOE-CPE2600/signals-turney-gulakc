/**
 * Modified by: Christian Gulak
 * 
 * Brief summary of modifications:
 * - Used sigqueue to send SIGUSR1 along with a random integer value.
 */

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <pid>\n", argv[0]);
        return 1;
    }

    pid_t pid = atoi(argv[1]);
    srand(time(NULL));
    int random_value = rand() % 100; // Generate a random number between 0 and 99

    // Create a union to send data with the signal
    union sigval value;
    value.sival_int = random_value;

    printf("Sending SIGUSR1 with value: %d to process %d\n", random_value, pid);
    sigqueue(pid, SIGUSR1, value);

    return 0;
}

