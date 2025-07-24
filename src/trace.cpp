#include "trace.hpp"
#include <algorithm>
#include <cmath>
#include <set>
#include <stdexcept>

namespace queueing {
std::vector<ServiceRecord> service_trace(std::vector<Arrival> arrivals,int servers,Policy policy) {
    if (servers<1 || arrivals.empty()) throw std::invalid_argument("arrivals and positive server count required");
    std::set<int> ids;
    for (const auto& job:arrivals) {
        if (!ids.insert(job.id).second || !std::isfinite(job.at) || job.at<0
                || !std::isfinite(job.service) || job.service<=0) throw std::invalid_argument("invalid arrival");
    }
    std::stable_sort(arrivals.begin(),arrivals.end(),[](const auto& a,const auto& b){return a.at<b.at;});
    std::vector<double> free(servers,0);
    std::vector<Arrival> waiting;
    std::vector<ServiceRecord> out;
    std::size_t next=0;
    while (out.size()<arrivals.size()) {
        auto available=std::min_element(free.begin(),free.end());
        double clock=*available;
        if (waiting.empty() && next<arrivals.size()) clock=std::max(clock,arrivals[next].at);
        while (next<arrivals.size() && arrivals[next].at<=clock) waiting.push_back(arrivals[next++]);
        if (waiting.empty()) continue;
        auto chosen=waiting.begin();
        if (policy==Policy::shortest) {
            chosen=std::min_element(waiting.begin(),waiting.end(),[](const auto& a,const auto& b){
                return a.service<b.service || (a.service==b.service && a.id<b.id);
            });
        } else if (policy==Policy::priority) {
            chosen=std::max_element(waiting.begin(),waiting.end(),[](const auto& a,const auto& b){
                return a.priority<b.priority || (a.priority==b.priority && a.id>b.id);
            });
        }
        const double start=std::max(*available,chosen->at);
        const int server=static_cast<int>(available-free.begin());
        out.push_back({chosen->id,server,chosen->at,start,start+chosen->service});
        *available=start+chosen->service;
        waiting.erase(chosen);
    }
    return out;
}
Summary summarize_trace(const std::vector<ServiceRecord>& records,int servers) {
    if (records.empty()||servers<1) throw std::invalid_argument("records and positive server count required");
    std::vector<double> waits;
    double busy=0,makespan=0,sum=0;
    for (const auto& record:records) {
        if (record.server<0||record.server>=servers||!std::isfinite(record.arrival)
                ||!std::isfinite(record.start)||!std::isfinite(record.finish)
                ||record.start<record.arrival||record.finish<=record.start) throw std::invalid_argument("invalid service record");
        waits.push_back(record.wait());sum+=record.wait();
        busy+=record.finish-record.start;makespan=std::max(makespan,record.finish);
    }
    std::sort(waits.begin(),waits.end());
    return {sum/records.size(),waits[static_cast<std::size_t>(.95*(waits.size()-1))],
            std::min(1.0,busy/(makespan*servers)),makespan};
}
} // namespace queueing
