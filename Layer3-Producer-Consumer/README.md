# Producer-Consumer – Layer 3

## Overview

Implemented the Producer-Consumer problem in C using POSIX threads and semaphores.
Simulates producers adding items to a shared buffer and consumers removing items, with proper synchronization to prevent race conditions.

## Synchronization Strategy

Used the **Three-Semaphore Solution**:

* `mutex` – binary semaphore for exclusive access to the buffer.
* `empty` – counting semaphore to track empty slots.
* `full` – counting semaphore to track full slots.

## Program Structure

* producer_consumer.c : main program with threads and semaphores
* Makefile : for building and cleaning
* README.md : this documentation
* test_output.txt : sample output

## How the Code Works

1. Created 2 producer threads and 3 consumer threads.
2. Producers wait if buffer is full; consumers wait if buffer is empty.
3. Mutex ensures only one thread accesses the buffer at a time.
4. Buffer is a circular array of size 5.

## Compilation

Using Makefile:

```
make
```

Or manually:

```
gcc producer_consumer.c -o producer_consumer -lpthread
```

## Execution

```
./producer_consumer
```

* Program continuously produces and consumes items.
* Stop with CTRL + C.

## Testing

* Program runs without race conditions.
* Buffer updates correctly.
* Sample output recorded in test_output.txt.

## Cleanup

```
make clean
```
