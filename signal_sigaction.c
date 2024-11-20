/**
 * @file signal_sigaction.c
 * @brief Program that registers a signal handler for SIGUSR1 using sigaction and exits after receiving the signal.
 */

/**
 * Modified by: Christian Gulak
 * 
 * Brief summary of modifications:
 * - Added logic to exit after receiving the signal.
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Flag to indicate when SIGUSR1 has been received
volatile sig_atomic_t signal_received = 0;


void handle_sigusr1(int sig, siginfo_t *siginfo, void *context) {
    printf("Received SIGUSR1 (Signal %d) from process %d\n", sig, siginfo->si_pid);
    signal_received = 1; 
}

int main() {
    struct sigaction sa;

    // Configure the sigaction structure
    sa.sa_flags = SA_SIGINFO; 
    sa.sa_sigaction = handle_sigusr1;  // assign it
    sigemptyset(&sa.sa_mask);  // Clear all 

    // Register the signal handler 
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    // Print the PID for other processes to send signals
    printf("Waiting for SIGUSR1... (PID: %d)\n", getpid());

    // Wait until SIGUSR1 is received
    while (!signal_received) {
        pause();  
    }

    printf("Exiting program after receiving SIGUSR1.\n");
    return 0;
}


