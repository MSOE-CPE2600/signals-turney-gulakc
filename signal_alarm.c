
/**
 * Modified by: Christian Gulak
 * singal-alarm.c
 * Brief summary of modifications:
 * - Added logic to stop the program after SIGALRM is received.
 * - Exits gracefully after the alarm signal is handled.
 */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// Flag to indicate when the alarm signal has been received
volatile sig_atomic_t alarm_received = 0;

void handle_alarm(int sig) {
    printf("Alarm received (Signal %d): 5 seconds elapsed.\n", sig);
    alarm_received = 1; 
}

int main() {
    // Register the signal handler 
    signal(SIGALRM, handle_alarm);

    // Set an alarm for 5 seconds
    alarm(5);

    // Infinite loop that terminates after alarm signal is received
    while (!alarm_received) {
        printf("Waiting for alarm...\n");
        sleep(1);
    }

    printf("Exiting program after alarm.\n");
    return 0;
}


