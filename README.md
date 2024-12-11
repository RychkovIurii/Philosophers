# Philosophers Project

## Table of Contents
- [Project Details](#project-details)
- [What I Learned](#what-i-learned)
- [Introduction](#introduction)
- [Main Features](#main-features)
- [Challenges](#challenges)
- [Allowed Functions](#allowed-functions)
- [Mandatory Part](#mandatory-part)
- [Bonus Part](#bonus-part)
- [Files](#files)
- [How to Run](#how-to-run)
- [Performance](#performance)

---

## Project Details
- **Total Time Spent**: 17 days
- **Total Lines of Code**: 1008
- **Commts**: 75
- **Programming Language**: C


---

## What I Learned
This project helped me deepen my understanding of multithreading, synchronization, and inter-process communication.  
Key takeaways include:
- `Thread Synchronization`: I learned to use mutexes and semaphores to prevent race conditions and ensure safe access to shared resources, such as forks in the philosophers' problem.  
- `Managing Processes and Threads`: In the bonus part, I explored the differences between threads and processes, and how they affect memory usage and synchronization.  
- `Deadlock and Starvation Handling`: I gained experience handling deadlock and starvation in concurrent systems, ensuring that all philosophers get the opportunity to eat without causing unnecessary delays or crashes.
- `Performance Optimization`: I learned how small optimizations, such as using multiple locks for distinct purposes, can significantly reduce delays and improve performance.  

This project sharpened my skills in multithreading, semaphores, and process management, as well as in analyzing and optimizing concurrency problems.


---

## Introduction
The **Philosophers** project simulates a classic synchronization problem involving multiple philosophers sitting at a round table, each alternating between thinking, eating, and sleeping.  
The goal is to avoid deadlock and starvation using multithreading or multiprocessing techniques.

### Philosophy Background
Philosophy (from Greek, *philosophia*—literally "love of wisdom") is the study of general and fundamental questions about existence, knowledge, values, reason, mind, and language. Philosophical methods include questioning, critical discussion, rational argument, and systematic presentation. The *Philosophers* project revolves around the coordination of actions and resources, which draws from philosophical ideas of behavior and time management.

---

## Main Features
- **Mandatory Part**: 
  - Each philosopher is a thread and alternates between eating, thinking, and sleeping.
  - Synchronization is ensured using mutexes for managing fork states.
  - Time constraints for each philosopher (time to die, eat, and sleep) are adhered to.
  
- **Bonus Part**: 
  - Each philosopher is a process, and they don't share memory.
  - Used semaphores to manage forks.

---

## Challenges
1. **Race Condition Avoidance**:
   - Prevented possible race conditions by using constant variables.
   - Decreased delays by using multiple locks, each dedicated to a specific purpose, to ensure safe access to resources.

2. **Bonus Implementation**:
   - In the bonus part, each philosopher is a process that doesn't share memory. 
   - Created separate threads for monitoring starvation and detached them to ensure proper synchronization and state checking.
   - Employed semaphores to manage fork states. A binary semaphore was used to print, ensuring only one philosopher could print at a time.
   - When a philosopher dies, all other processes are killed to prevent further actions in the simulation.

---

## Allowed Functions
- **Mandatory Part**:
memset, printf, malloc, free, write, usleep, gettimeofday, pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock.
- **Bonus Part** (Processes & Semaphores):
memset, printf, malloc, free, write, fork, kill, exit, pthread_create, pthread_detach, pthread_join, usleep, gettimeofday, waitpid, sem_open, sem_close, sem_post, sem_wait, sem_unlink.

---

## Mandatory Part
The mandatory part involves creating a simulation where philosophers take turns eating, thinking, and sleeping using **threads** and **mutexes** to ensure synchronization. Each philosopher shares a fork with their neighboring philosopher, and mutexes are used to avoid duplicate fork access.

### Requirements:
- **Arguments**: `number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]`
  - `number_of_philosophers`: Number of philosophers (and forks).
  - `time_to_die`: Time a philosopher can survive without eating.
  - `time_to_eat`: Time taken to eat.
  - `time_to_sleep`: Time spent sleeping.

- **External Functions**: `memset`, `printf`, `malloc`, `free`, `write`, `usleep`, `gettimeofday`, `pthread_create`, `pthread_detach`, `pthread_join`, `pthread_mutex_init`, `pthread_mutex_destroy`, `pthread_mutex_lock`, `pthread_mutex_unlock`

---

## Bonus Part
The bonus part extends the simulation by using **processes** and **semaphores**. Each philosopher is represented as a separate process, and semaphores are used to synchronize fork access. The simulation is designed such that philosophers are not allowed to share memory, and starvation is detected and handled with additional threads.

### Requirements:
- **Arguments**: `number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]`
- **External Functions**: `memset`, `printf`, `malloc`, `free`, `write`, `fork`, `kill`, `exit`, `pthread_create`, `pthread_detach`, `pthread_join`, `usleep`, `gettimeofday`, `waitpid`, `sem_open`, `sem_close`, `sem_post`, `sem_wait`, `sem_unlink`

---

## Files
- **`philo.c`**: Main implementation for the mandatory part.
- **`philo_bonus.c`**: Bonus part implementation, handling processes and semaphores.
- **`Makefile`**: Used to compile the project.
- **`philo.h`**: Header file containing function declarations and constants.

---

## How to Run
Clone the repository:

```bash
git clone https://github.com/RychkovIurii/Philosophers.git
```

Navigate to folder:
```bash
cd philo
```

Compile the project using the Makefile:

```bash
make
```
Run the mandatory part:

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```
Run the bonus part:

```bash
./philo_bonus <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```
## Performance
- Mandatory Part: Around `2ms` to launch 200 philosophers.
- Bonus Part: Around `11ms` to launch 200 philosophers.
