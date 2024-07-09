# Philosophers

The Philosophers project at 42 is a common multi-threading programming exercise based on the famous "Dining Philosophers" problem, formulated by Edsger Dijkstra. The problem involves a scenario with five philosophers who alternately think and eat. They sit at a table with five plates and five forks. Each philosopher needs two forks to eat, but there are only five forks available. The challenge is to design a concurrency solution that ensures no philosopher starves (each can eventually eat), avoids deadlock (where philosophers could be stuck waiting forever for a fork), and avoids unnecessary delays (philosophers shouldn't wait if forks are available).

Key concepts and goals of the project include:

1. **Concurrency and Synchronization**: Understanding how to manage concurrent operations and ensure proper synchronization between threads.
2. **Mutexes and Semaphores**: Learning to use mutexes (mutual exclusions) and semaphores to control access to shared resources.
3. **Deadlock Avoidance**: Designing a system that avoids deadlocks by ensuring that resource acquisition does not lead to a circular wait condition.
4. **Starvation Prevention**: Ensuring that each philosopher gets the opportunity to eat without any philosopher being perpetually deprived of resources.

The project helps students gain practical experience with threading, synchronization mechanisms, and techniques to manage concurrent processes effectively.

## Usage

Compile the project using the provided Makefile. Run the program with the desired number of philosophers, time to die, time to eat, time to sleep, and an optional number of times each philosopher must eat.

```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

For example:

```
./philo 5 800 200 200
```
In this case no one should die.

```
./philo 5 800 200 200 7
```
No one should die and the simulation should stop when all the philosopher has eaten at least 7 times each.

```
./philo 5 800 200 200 7
```
A philosopher should die.
