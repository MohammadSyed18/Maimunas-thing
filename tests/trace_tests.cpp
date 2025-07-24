#include "trace.hpp"
#include "sensitivity.hpp"
#include <cassert>
#include <cmath>
#include <stdexcept>
using namespace queueing;
int main() {
    std::vector<Arrival> arrivals{{0,0,10,1},{1,1,5,2},{2,2,1,5}};
    auto fifo=service_trace(arrivals,1,Policy::fifo);
    auto shortest=service_trace(arrivals,1,Policy::shortest);
    assert(fifo[1].id==1&&shortest[1].id==2);
    assert(fifo[1].wait()==9&&shortest[1].wait()==8);
    auto priority=service_trace(arrivals,1,Policy::priority);
    assert(priority[1].id==2);
    assert(summarize_trace(fifo,1).makespan==16);
    auto parallel=service_trace(arrivals,2,Policy::fifo);
    for (std::size_t i=0;i<parallel.size();++i) for (std::size_t j=i+1;j<parallel.size();++j)
        if(parallel[i].server==parallel[j].server) assert(parallel[j].start>=parallel[i].finish);
    bool rejected=false;try{service_trace({{1,0,-1,0}},1,Policy::fifo);}catch(const std::invalid_argument&){rejected=true;}
    assert(rejected);
    Config config;config.customers=30;
    auto first=compare_paired(config,4);auto second=compare_paired(config,4);
    assert(first[0].mean_wait_difference==second[0].mean_wait_difference);
    assert(first[0].confidence95>=0);
    assert(comparisons_csv(first).find("shortest,4")!=std::string::npos);
}
