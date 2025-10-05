#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include <vector>
#include "random_cell_generator.h"

struct ExperimentResult {
    double mean;
    double median;
    std::vector<int> free_zone_sizes;
};

class Experiment {

    int board_size;
    int num_experiments;

public:
    Experiment(int n, int experiments = 1000);

    ExperimentResult run(int m);
};

#endif