/**
 * @file signal_segfault.c
 * @brief Program that handles SIGSEGV and demonstrates its behavior.
 */

/**
 * Modified by: Christian Gulak
 * 
 * Brief summary of modifications:
 * - Added a signal handler for SIGSEGV.
 * - Printed a message when SIGSEGV is received.
 * - Returned from the handler to observe behavior.
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>


void handle_sigsegv(int sig) {
    printf("Caught SIGSEGV (Signal %d): Segmentation fault occurred.\n", sig);
    // Return without resolving the issue to observe repeated behavior
}

int main() {
    signal(SIGSEGV, handle_sigsegv);

    // Declare a null pointer
    int* i = NULL;

    // cause a segmentation fault
    printf("The value of i is: %d\n", *i);

    return 0;
}
