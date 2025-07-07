#include "simulator.hpp"
#include <cassert>
#include <iostream>
int main(){queueing::Config c{200,2,.7,.6,123,queueing::Policy::fifo};auto a=queueing::simulate(c),b=queueing::simulate(c);assert(a.mean_wait==b.mean_wait);assert(a.utilization>=0&&a.utilization<=1);c.policy=queueing::Policy::shortest;auto shortest=queueing::simulate(c);assert(shortest.mean_wait<=a.mean_wait);bool threw=false;try{queueing::simulate({0,1,.2,.3,1,queueing::Policy::fifo});}catch(...){threw=true;}assert(threw);std::cout<<"queue simulator tests passed\n";}
