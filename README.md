# Maimuna's thing

A C++20 discrete-event simulator for comparing service-line policies in synthetic schools, clinics, or community centers. It supports three queue policies, seeded arrivals/service, multiple servers, configuration validation, repeated experiments, policy comparisons, standard deviation and 95% confidence intervals, plus wait, utilization, and makespan metrics.

Run `cmake -S . -B build && cmake --build build`, `ctest --test-dir build --output-on-failure`, and `./build/queue-sim sample/clinic.conf`. Results are simulation estimates, not operational promises; the model currently assumes independent exponential timing.
