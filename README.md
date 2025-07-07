# Maimuna's thing

A C++20 discrete-event simulator for comparing service-line policies in synthetic schools, clinics, or community centers. It supports FIFO, shortest-service-first, and priority queues; seeded exponential arrivals/service times; multiple servers; configuration files; and mean wait, p95 wait, utilization, and makespan statistics.

Run `cmake -S . -B build && cmake --build build`, `ctest --test-dir build --output-on-failure`, and `./build/queue-sim sample/clinic.conf`. Results are simulation estimates, not operational promises; the model currently assumes independent exponential timing.
