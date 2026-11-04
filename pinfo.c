/*
* Logan Amar
* Lab 9 - System Calls
* CPE 2600
* Description: 
* pinfo.c
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sched.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/types.h>

static const char *policy_to_string(int policy){
    switch (policy){
        case SCHED_OTHER: return "SCHED_OTHER";
        case SCHED_FIFO:  return "SCHED_FIFO";
        case SCHED_RR:    return "SCHED_RR";
        case SCHED_BATCH: return "SCHED_BATCH";
        case SCHED_IDLE:  return "SCHED_IDLE";
        default: return "UNKNOWN";
    }
}

int main(int argc, char* argv[]){

    pid_t pid;

    if (argc > 2){
        fprintf(stderr, "Usage: %s [pid]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argc == 2){
        // Convert the argument to a number and make sure the whole
        // string was a valid positive integer.
        char* end;
        errno = 0;
        long value = strtol(argv[1], &end, 10);
        if (errno != 0 || *end != '\0' || end == argv[1] || value <= 0){
            fprintf(stderr, "Error: '%s' is not a valid process id\n", argv[1]);
            return 1;
        }

        pid = (pid_t)value;
    } else {
        pid = getpid();
    }

    errno = 0;
    int prio = getpriority(PRIO_PROCESS, pid);
    if (errno != 0) {
        perror("Invalid process");
        exit(EXIT_FAILURE);
        /* TODO: perror + exit(EXIT_FAILURE) */
    }

    int policy = sched_getscheduler(pid);
    /* TODO: error check (-1) */

    printf("PID: %d\nPriority: %d\nScheduler: %s\n", pid, prio, policy_to_string(policy));

    return 0;
}