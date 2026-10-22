# Maimuna's thing

A C++20 queue simulator. Compares three service-line policies with seeded arrivals, multiple servers, and repeated runs.

Reports wait times, utilization, makespan, standard deviation, and 95% confidence intervals.

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/queue-sim sample/clinic.conf
```

These are simulation results, not predictions for a real clinic or school. The model currently assumes independent exponential timing.
