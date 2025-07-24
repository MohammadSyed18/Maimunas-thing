#include "sensitivity.hpp"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace queueing {
std::vector<PairedComparison> compare_paired(Config config,int count) {
    if (count<2||count>100000) throw std::invalid_argument("replications must be 2..100000");
    std::vector<PairedComparison> out;
    const auto seed=config.seed;
    for (auto policy:{Policy::shortest,Policy::priority}) {
        double mean=0,m2=0;int improved=0;
        for (int i=0;i<count;++i) {
            config.seed=seed+static_cast<std::uint64_t>(i);config.policy=Policy::fifo;
            double baseline=simulate(config).mean_wait;
            config.policy=policy;
            double difference=simulate(config).mean_wait-baseline;
            if (difference<0) ++improved;
            double delta=difference-mean;mean+=delta/(i+1);m2+=delta*(difference-mean);
        }
        double sd=std::sqrt(std::max(0.0,m2/(count-1)));
        out.push_back({policy,count,mean,1.96*sd/std::sqrt(count),improved});
    }
    return out;
}
std::string comparisons_csv(const std::vector<PairedComparison>& comparisons) {
    std::ostringstream out;out<<std::setprecision(10);
    out<<"candidate,replications,mean_wait_difference,normal95_half_width,improved_runs\n";
    for (const auto& row:comparisons) out<<policy_name(row.candidate)<<','<<row.replications<<','
        <<row.mean_wait_difference<<','<<row.confidence95<<','<<row.improved_runs<<'\n';
    return out.str();
}
}
