# Philosophers
<br>
<p align="center">
    <img src=https://upload.wikimedia.org/wikipedia/commons/7/7b/An_illustration_of_the_dining_philosophers_problem.png alt="Dining Philosophers illustration" width="200">
</p>

### Skills

- Multithreading with **pthreads**
- Synchronization using **mutexes**
- Avoiding **race conditions** and **deadlocks**
- Precise **time management** (`gettimeofday`, custom sleep functions)
- Parsing and validating program arguments
- Resource cleanup and error handling

<br>

## About

`philosophers` is a simulation of the classic **Dining Philosophers Problem**, a classic concurrency problem illustrating **synchronization challenges**.

A number of philosophers sit around a table. Each philosopher alternates between **thinking**, **eating**, and **sleeping**. To eat, a philosopher needs **two forks**, but forks are shared with their neighbors.

The program ensures philosophers do not starve and that no deadlocks occur.

**Rules**
- Each philosopher:
    - Thinks
    - Picks up forks (left and right)
    - Eats for a given time
    - Sleeps for a given time
    - Repeats the cycle
- If a philosopher doesn't eat within the allowed time (`time_to_die`), they die.
- The simulation stops when a philosopher dies, or when all philosophers have eaten the required number of times (if specified).

<br>

## Usage

**1. Clone the repository**
```bash
git clone git@github.com:maudiffr/Philosophers.git
cd Philosophers/philo
```

**2. Compile the project**
```bash
make
```

**3. Run the program**
```bash
./philo number_of_philos time_to_die time_to_eat time_to_sleep [number_of_times_each_philo_must_eat]
```
- `number_of_philos` &rarr; number of philosophers (and forks)
- `time_to_die` &rarr; time (ms) before a philosopher dies without eating
- `time_to_eat` &rarr; time (ms) spent eating
- `time_to_sleep` &rarr; time (ms) spent sleeping
- `number_of_times_each_philo_must_eat` &rarr; (optional) stop condition

<br>

## Example

```bash
./philo 5 800 200 200
```
&rarr; 5 philosophers, each will die if they don't eat for 800ms. Eating takes 200ms, sleeping takes 200ms.

```bash
./philo 5 800 200 200 7
```
&rarr; Same as above, but simulation stops once each philosopher has eaten 7 times.

**Logs format**

Each log line follows the format:
```csharp
[timestamp_in_ms] philosopher_id action
```
