/*
* Logan Amar
* Lab 9 - System Calls
* CPE 2600
* Description: 
* info.c
*/

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>

/* Print label + value only if value is non-empty */
static void print_if_set(const char *label, const char *value){
    if (value != NULL && value[0] != '\0'){
        printf("%s: %s\n", label, value);
    }
}

int main(void){

    struct timespec ts;
    struct utsname u;

    if (clock_gettime(CLOCK_REALTIME, &ts) == -1){
        perror("clock_gettime");
        return 1;
    }

    long long ns = (long long)ts.tv_sec * 1000000000LL + ts.tv_nsec;
    printf("Clock time: %lld\n", ns);

    uname(&u);

    print_if_set("Network name: ", u.nodename);
    print_if_set("System name: ", u.sysname);
    print_if_set("Release: ", u.release);
    print_if_set("Version: ", u.version);
    print_if_set("Hardware: ", u.machine);

    printf("CPUs: %d\n", get_nprocs());

    long long page = sysconf(_SC_PAGESIZE);
    long long total = (long long)sysconf(_SC_PHYS_PAGES) * page;
    long long free_mem = (long long)sysconf(_SC_AVPHYS_PAGES) * page;

    printf("Total physical memory: %lld bytes\n", total);
    printf("Free memory: %lld bytes\n", free_mem);

    return 0;
}