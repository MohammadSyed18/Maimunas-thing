#include "experiment.hpp"
#include "config_validation.hpp"
#include <cassert>
namespace {struct Run{Run(){queueing::Config c{100,2,.4,.5,10,queueing::Policy::fifo};auto a=queueing::replicate(c,5);assert(a.replications==5);assert(a.confidence95>=0);auto policies=queueing::compare_policies(c,3);assert(policies.size()==3);assert(queueing::validate_config(c).empty());c.arrival_rate=2;assert(!queueing::validate_config(c).empty());}} run;}
