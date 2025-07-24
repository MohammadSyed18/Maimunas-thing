# maimuna's thing

a C++20 queue simulator. compares three service-line policies with seeded arrivals, multiple servers, and repeated runs.

reports wait times, utilization, makespan, standard deviation, and 95% confidence intervals.

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/queue-sim sample/clinic.conf
```

these are simulation results, not predictions for a real clinic or school. the model currently assumes independent exponential timing.

## Implementation details

Replicated experiments use numerically stable online variance with a sample standard deviation. Policy comparisons share the same replication seeds, and simulations reject non-finite rates.

## Inspectable traces and paired experiments

[trace.hpp](include/trace.hpp) and [trace.cpp](src/trace.cpp) accept explicit arrivals and return each job's server, arrival, service start, finish, and waiting time. This makes FIFO, shortest-job, and priority behavior inspectable without relying only on an aggregate random simulation.

[sensitivity.cpp](src/sensitivity.cpp) compares each alternative with FIFO using the same seed per replication and reports the paired waiting-time difference, its normal-approximation 95% half-width, and the number of improved runs.

```sh
./build/queue-experiment sample/clinic.conf 100
```

Negative differences mean lower waiting time than FIFO. Intervals describe variation under this simulator's assumptions, not real-world causal performance. Tests cover exact small traces, parallel-server non-overlap, invalid service times, and reproducible paired results.
