# CPE 2600 Lab 9: System Calls

**Author:** Logan Amar
**Course:** CPE 2600 Systems Programming
**Section:** CPE2600

## Overview

| Source file | Executable | Category |
|-------------|------------|----------|
| `info.c`    | `info`     | Information maintenance |
| `pinfo.c`   | `pinfo`    | Process control (retrieving process info) |
| `pmod.c`    | `pmod`     | Process control (altering a process) |
| `finfo.c`   | `finfo`    | File management |

### info

Prints system information gathered with `clock_gettime`, `uname`,
`get_nprocs`, and `sysconf`:

- Current time of day in nanoseconds
- Network name, operating system name, release, version, and hardware type
- Number of CPUs
- Total and free physical memory in bytes

Any value that comes back as an empty string is not printed.

```
./info
```

### pinfo

Prints the priority and scheduling policy (as text, such as `SCHED_OTHER`)
of a process, using `getpriority` and `sched_getscheduler`.

```
./pinfo          # current process
./pinfo <pid>    # specified process
```

Prints an error and exits if the PID is invalid or does not exist, or if
more than one argument is given.

### pmod

Lowers its own priority by 10 using `nice(10)`, sleeps for
1,837,272,638 nanoseconds (1 s + 837,272,638 ns) using `nanosleep`, then
prints a goodbye message and exits. If a signal interrupts the sleep, the
program resumes sleeping for the remaining time.

```
./pmod
```

**Observation in top/htop:** while running, the process showed a nice value
(NI) of <observed value> and a priority (PR) of <observed value>. Because
the sleep is short, this was observed by temporarily lengthening the sleep.
The final code uses the required value.

### finfo

Displays information about a file given on the command line, using `lstat`:

- File type (regular file, directory, symbolic link, etc.)
- Permissions in `rwxrwxrwx` form
- Owner user ID
- Size in bytes
- Date and time of last modification

```
./finfo <filename>
```