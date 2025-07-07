#pragma once
#include <cstdint>
#include <string>
namespace queueing {enum class Policy{fifo,shortest,priority};struct Config{int customers=100;int servers=2;double arrival_rate=.4;double service_rate=.5;std::uint64_t seed=42;Policy policy=Policy::fifo;};struct Summary{double mean_wait{};double p95_wait{};double utilization{};double makespan{};};Config read_config(const std::string&);Summary simulate(const Config&);std::string policy_name(Policy);}
