/*
* Logan Amar
* Lab 9 - System Calls
* CPE 2600
* Description: Prints file info for given filename
* finfo.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

static const char *file_type(mode_t m)
{
    if (S_ISREG(m)) return "regular file";
    if (S_ISDIR(m)) return "directory";
    if (S_ISBLK(m)) return "block device";
    if (S_ISCHR(m)) return "character device";
    if (S_ISFIFO(m)) return "FIFO";
    if (S_ISLNK(m)) return "symbolic link";
    if (S_ISSOCK(m)) return "socket";
    return "unknown";
}

static void print_perms(mode_t m)
{
    char p[10];
    p[0] = (m & S_IRUSR) ? 'r' : '-';
    p[1] = (m & S_IWUSR) ? 'w' : '-';
    p[2] = (m & S_IXUSR) ? 'x' : '-';

    p[3] = (m & S_IRGRP) ? 'r' : '-';
    p[4] = (m & S_IRGRP) ? 'w' : '-';
    p[5] = (m & S_IRGRP) ? 'x' : '-';

    p[6] = (m & S_IROTH) ? 'r' : '-';
    p[7] = (m & S_IROTH) ? 'w' : '-';
    p[8] = (m & S_IROTH) ? 'x' : '-';

    p[9] = '\0';
    printf("Permissions: %s\n", p);
}

int main(int argc, char *argv[])
{
    struct stat sb;

    if (argc != 2){
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (lstat(argv[1], &sb) == -1){
        perror("lstat");
        return EXIT_FAILURE;
    }

    printf("Type: %s\n", file_type(sb.st_mode));
    print_perms(sb.st_mode);
    printf("Owner UID: %u\n", (unsigned)sb.st_uid);
    printf("Size: %lld bytes\n", (long long)sb.st_size);

    char timebuf[64];
    struct tm *tm = localtime(&sb.st_mtime);
    
    if (tm != NULL){
        strftime(timebuf, sizeof timebuf, "%Y-%m-%d %H:%M:%S", tm);
    }

    printf("Last modified: %s\n", timebuf);

    return 0;
}