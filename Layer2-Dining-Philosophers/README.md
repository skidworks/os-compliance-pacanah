# Dining Philosophers – Layer 2

## Overview
Implemented the Dining Philosophers problem in C using POSIX threads and semaphores. 
Simulates 5 philosophers alternating between thinking and eating while sharing chopsticks. 
Deadlock-prevention strategy is included.

## Deadlock Prevention Strategy
Used the Asymmetric Strategy:
- Odd-numbered philosophers pick up left chopstick first, then right.
- Even-numbered philosophers pick up right chopstick first, then left.
This prevents circular wait and avoids deadlock.

## Program Structure
- dining_philosophers.c : main program with threads and semaphores
- Makefile : for building and cleaning
- README.md : this documentation
- test_output.txt : sample output

## How the Code Works
1. Created 5 philosopher threads using pthreads.
2. Each chopstick is represented by a semaphore.
3. Each philosopher repeatedly thinks, picks up chopsticks (asymmetric), eats, and puts down chopsticks.

## Compilation
Using Makefile:
make

Or manually:
gcc dining_philosophers.c -o dining -pthread

## Execution
./dining
- Run for 3-5 minutes to ensure no deadlock.
- Stop with CTRL + C.

## Testing
- Program runs without deadlock.
- All philosophers eat regularly.
- Sample output recorded in test_output.txt.

## Cleanup
make clean
