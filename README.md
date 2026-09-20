*This project has been created as part of the 42 curriculum by ybourajl.*

# Codexion

## Description
**Codexion** is a complex multithreading and resource management simulation inspired by the classic Dining Philosophers problem, tailored to a software development environment. In this simulation, a group of coders must share a limited number of hardware dongles to complete their work cycle: compiling, debugging, and refactoring. Because each coder requires two specific dongles to compile their code, the primary goal of this project is to manage concurrent thread execution, allocate shared resources fairly, and prevent coders from "burning out" (starving) before they meet their deadlines.

## Instructions

### Compilation
The project includes a `Makefile`. To compile the program, simply run:
```bash
make
```
This will generate the codexion executable. Additional rules include make clean, make fclean, and make re.
Execution

Run the executable with the following arguments (time is in milliseconds):
```Bash

./codexion <number_of_coders> <time_to_burnout> <time_to_compile> <time_to_debug> <time_to_refactor> [number_of_times_each_coder_must_compile] [cooldown] [algorithm]
```
Example:

```Bash

./codexion 3 70000 25 25 25 3 450 fifo
```

To stop the simulation manually if it runs indefinitely, use CTRL+C.
Blocking Cases Handled

## This project handles several advanced concurrency issues and edge cases:
-
    Deadlock Prevention (Coffman's Conditions): A classic circular wait deadlock occurs when all coders grab their left dongle simultaneously, leaving no right dongles available. This is prevented by breaking the symmetry: even-indexed coders pick up their left dongle first, while odd-indexed coders pick up their right dongle first.
-
    Starvation Prevention: To ensure no coder is left waiting indefinitely while neighbors monopolize the dongles, a custom priority queue (min-heap) is used. Coders are sorted based on their last compile time and total number of compilations.
-
    Cooldown Handling: Dongles are not immediately usable after release. They feature an available_at_ms property, and threads will wait until the mandatory cooldown period expires before re-acquiring them.
-
    Precise Burnout Detection: A dedicated monitor thread continuously checks the timestamp of every coder. If the time elapsed since a coder's last compile start exceeds the time_to_burnout, the monitor immediately flags the simulation as stopped and broadcasts to all threads to exit gracefully.
-
    Log Serialization: To prevent garbled console output (where multiple threads print at the exact same microsecond), all terminal logging is protected by a centralized print_lock mutex.

# Thread Synchronization Mechanisms

The core of this simulation relies on POSIX threading primitives to ensure data integrity and safe communication:
-
    pthread_mutex_t: Mutexes are heavily utilized to protect shared variables from race conditions. Dedicated mutexes protect the central wait queue, individual coder timestamps (last_compile_start_mut), and the global simulation state (e.g., checking if someone has burned out).
-
    pthread_cond_t: Condition variables are used to orchestrate thread wake-ups without wasting CPU cycles via busy-waiting (spinlocks). Each coder has a personal_cond variable.
-
    Thread-Safe Resource Allocation: When a coder attempts to acquire dongles, they lock the queue mutex and insert themselves into the priority heap. They then enter a pthread_cond_wait loop that only unblocks when two conditions are met: (1) both required dongles are completely free, and (2) the coder is currently at the root (top priority) of the min-heap.
-
    Coder-Monitor Communication: The monitor thread safely reads each coder's state by locking that specific coder's timestamp mutex before reading last_compile_start. When the monitor detects a burnout, it flips a global stopped flag and uses pthread_cond_broadcast(&sim->state_cond) to instantly wake up all sleeping coders so they can exit their routines cleanly, preventing hanging threads.

# Resources
-
    Documentation & Articles:

        POSIX Threads Programming (Lawrence Livermore National Laboratory):
            https://hpc-tutorials.llnl.gov/posix

        Wikipedia: Dining Philosophers Problem
            https://en.wikipedia.org/wiki/Dining_philosophers_problem?
        other:
            https://www.geeksforgeeks.org/c/c-program-to-implement-min-heap/
            https://medium.com/@samiracppdev/and-7e2a0793f9a9