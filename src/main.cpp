#include "simulator.hpp"
#include <iomanip>
#include <iostream>
int main(int argc,char**argv){if(argc!=2){std::cerr<<"usage: queue-sim <config>\n";return 2;}try{auto c=queueing::read_config(argv[1]);auto s=queueing::simulate(c);std::cout<<std::fixed<<std::setprecision(3)<<"policy="<<queueing::policy_name(c.policy)<<" mean_wait="<<s.mean_wait<<" p95_wait="<<s.p95_wait<<" utilization="<<s.utilization<<" makespan="<<s.makespan<<"\n";}catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;}}
