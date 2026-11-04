/*
* Logan Amar
* Lab 9 - System Calls
* CPE 2600
* Description: 
* pmod.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>

int main(void){
    
    struct timespec req = { .tv_sec = 1, .tv_nsec = 837272638 };
    struct timespec rem;

    errno = 0;
    int new_nice = nice(10);   //positive = LOWER priority
    if (new_nice == -1 && errno != 0){
        perror("");
    }

    printf("New nice value: %d\n", new_nice);

    while(nanosleep(&req, &rem) == -1){
        if (errno != EINTR){
            perror("nanosleep");
            exit(EXIT_FAILURE);
        }
        req = rem;
    }

    printf("Goodbye!\n");
    return 0;
}