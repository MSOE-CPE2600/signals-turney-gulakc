/**
 * Modified by: Christian Gulak
 * 
 * Brief summary of modifications:
 * - Used sigaction to handle SIGUSR1.
 * - Extracted and printed the integer value sent with the signal.
 * * Command to send SIGUSR1:
 * - Using the `kill` command:
 *   `kill -SIGUSR1 <Pid>`
 *   Replace `<Pid>` with the process ID of the running `recv_signal` program.
 * 
 * Example:
 * 1. Run `./recv_signal`, note the PID output 
 * 2. In another terminal, execute `kill -SIGUSR1 <Pid>
 */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>


void handle_sigusr1(int sig, siginfo_t *info, void *context) {
    printf("Received SIGUSR1 (Signal %d) with data: %d\n", sig, info->si_value.sival_int);
}

int main() {
    struct sigaction sa;

    // Configure sigaction to use handle_sigusr1 and allow access to signal info
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handle_sigusr1;
    sigaction(SIGUSR1, &sa, NULL);

    printf("Waiting for SIGUSR1... (PID: %d)\n", getpid());

    // Infinite loop to keep the program running
    while (1) {
        pause(); // Wait for a signal
    }

    return 0;
}

