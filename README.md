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
