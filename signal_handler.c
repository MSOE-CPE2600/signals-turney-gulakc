/**
 * Modified by: Christian Gulak
 * 
 * Brief summary of modifications:
 * - Modified the infinite loop to terminate the program by sending a SIGKILL signal to itself.
 */



#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


void handle_signal(int sig) {
    printf("Received SIGINT (Signal %d). Program will continue running.\n", sig);
}

int main() {
    // Register the signal handler for SIGINT
    signal(SIGINT, handle_signal);

    // Print the PID for reference
    printf("Program is running (PID: %d).\n", getpid());
    printf("Send SIGINT (Ctrl+C) to see the handler in action.\n");

    // Infinite loop 
    while (1) {
        printf("Sleeping...\n");
        sleep(3); // Simulate work

        // Terminate by sending SIGKILL to itself
        printf("Self-terminating using SIGKILL...\n");
        kill(getpid(), SIGKILL);
    }

    return 0;
}


