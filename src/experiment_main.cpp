#include "sensitivity.hpp"
#include <iostream>
#include <exception>

int main(int argc,char** argv) {
    if (argc!=3) {std::cerr<<"usage: queue-experiment <config> <replications>\n";return 2;}
    try {
        std::cout<<queueing::comparisons_csv(queueing::compare_paired(queueing::read_config(argv[1]),std::stoi(argv[2])));
    } catch (const std::exception& error) {std::cerr<<error.what()<<'\n';return 1;}
}
