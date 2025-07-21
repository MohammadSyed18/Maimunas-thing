#pragma once
#include "simulator.hpp"
#include <vector>
namespace queueing {struct Aggregate{double mean_wait{};double wait_stddev{};double mean_utilization{};double confidence95{};int replications{};};Aggregate replicate(Config,int);struct PolicyResult{Policy policy;Aggregate aggregate;};std::vector<PolicyResult> compare_policies(Config,int);}
