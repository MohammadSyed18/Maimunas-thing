#pragma once
#include "simulator.hpp"
#include <vector>

namespace queueing {
struct Arrival {
    int id{};
    double at{};
    double service{};
    int priority{};
};
struct ServiceRecord {
    int id{};
    int server{};
    double arrival{};
    double start{};
    double finish{};
    double wait() const { return start-arrival; }
};
std::vector<ServiceRecord> service_trace(std::vector<Arrival> arrivals,int servers,Policy policy);
Summary summarize_trace(const std::vector<ServiceRecord>& records,int servers);
} // namespace queueing
