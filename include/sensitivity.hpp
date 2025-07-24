#pragma once
#include "simulator.hpp"
#include <string>
#include <vector>

namespace queueing {
struct PairedComparison {
    Policy candidate;
    int replications{};
    double mean_wait_difference{};
    double confidence95{};
    int improved_runs{};
};
std::vector<PairedComparison> compare_paired(Config config,int count);
std::string comparisons_csv(const std::vector<PairedComparison>& comparisons);
}
