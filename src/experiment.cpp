#include "experiment.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace queueing {
Aggregate replicate(Config config, int count) {
    if (count < 2) throw std::invalid_argument("at least two replications required");
    double mean=0, second_moment=0, utilization=0;
    const auto base_seed=config.seed;
    for (int i=0;i<count;++i) {
        config.seed=base_seed+static_cast<std::uint64_t>(i);
        const auto result=simulate(config);
        const double delta=result.mean_wait-mean;
        mean+=delta/(i+1);
        second_moment+=delta*(result.mean_wait-mean);
        utilization+=result.utilization;
    }
    const double sd=std::sqrt(std::max(0.0,second_moment/(count-1)));
    // Normal-approximation half-width; report the replication count with it.
    return {mean,sd,utilization/count,1.96*sd/std::sqrt(count),count};
}
std::vector<PolicyResult> compare_policies(Config config,int count) {
    std::vector<PolicyResult> out;
    for(auto policy:{Policy::fifo,Policy::shortest,Policy::priority}) {
        config.policy=policy;
        out.push_back({policy,replicate(config,count)});
    }
    return out;
}
}
