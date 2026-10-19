# Philosophers

A solution to the classic **dining philosophers** concurrency problem in C, using POSIX threads and mutexes.

N philosophers sit around a table with one fork between each pair. To eat, a philosopher needs both neighbouring forks. Each one cycles through *eating → sleeping → thinking*, and the simulation must stop as soon as someone goes too long without eating. The challenge is to share the forks without deadlocks, data races or starvation, and to detect a death on time.

## How it works

- **One thread per philosopher, plus one monitor thread.** Philosopher threads run the eat / sleep / think loop. The monitor checks every philosopher roughly once per millisecond and reports a death as soon as the time since the last meal exceeds `time_to_die`.
- **One mutex per fork.** Separate mutexes protect each philosopher's meal data, the shared "someone died" flag and the console output, so log lines never interleave.
- **Deadlock prevention through lock ordering.** Odd and even philosophers pick up their forks in opposite order, so a circular wait in which everyone holds one fork can never form.
- **Synchronised start.** All threads wait for a shared start timestamp before running, so nobody gets a head start. Odd philosophers begin by thinking, which staggers the first round of fork requests.
- **Starvation control.** Thinking time is calculated from how much time a philosopher has left before dying, so hungrier philosophers return to the table sooner. Odd-sized tables use a shorter wait.
- **Edge cases.** A single philosopher (only one fork) is handled separately. Input is validated: numeric arguments only, and 1–200 philosophers.

The project is compiled with **ThreadSanitizer** (`-fsanitize=thread`) to catch data races during development.

## Build and run

```bash
cd philo
make
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_meals]
```

Times are in milliseconds. The optional last argument stops the simulation once every philosopher has eaten that many times.

```bash
./philo 5 800 200 200        # nobody should die
./philo 4 310 200 100        # a philosopher dies
./philo 5 800 200 200 7      # stops after every philosopher has eaten 7 times
```

Example output (timestamp in ms, philosopher id, action):

```
0     1   has taken a fork
0     1   has taken a fork
0     1   is eating
200   1   is sleeping
...
```

## Project structure

```
philo/
├── main.c                  # setup, thread creation and joining
├── include/philo.h         # shared structs and prototypes
└── src/
    ├── check_input.c       # argument validation
    ├── init_structs.c      # mutex and struct initialisation
    ├── forks.c             # fork pick-up order (deadlock prevention)
    ├── life.c              # eat / sleep / think loop
    ├── monitoring_thread.c # death detection and synchronised start
    ├── destroy_struct.c    # cleanup
    └── utils.c             # time, logging, helpers
```

Part of the [Codam](https://www.codam.nl/) (42 Network) curriculum.
