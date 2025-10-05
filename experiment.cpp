#include "experiment.h"
#include <iostream>
#include <algorithm>
#include "board.h"
#include "random_cell_generator.h"

Experiment::Experiment(int n, int experiments)
    : board_size(n), num_experiments(experiments) {
    if (n <= 0 || experiments <= 0) {
        throw std::invalid_argument("Invalid experiment parameters");
    }
}

ExperimentResult Experiment::run(int m) {
    if (m < 0 || m > board_size * board_size) {
        throw std::invalid_argument("Invalid number of cells to select");
    }

    std::vector<int> free_zone_sizes;
    free_zone_sizes.reserve(num_experiments);

    for (int exp = 0; exp < num_experiments; ++exp) {
        Board board(board_size);
        RandomCellGenerator generator(board_size);
        for (int i = 0; i < m; ++i) {
            Cell random_cell = generator();
            board.addSelectedCell(random_cell);
        }

        free_zone_sizes.push_back(board.calculateFreeZoneSize());
    }

    double mean = std::accumulate(free_zone_sizes.begin(),
        free_zone_sizes.end(), 0.0) / num_experiments;

    std::sort(free_zone_sizes.begin(), free_zone_sizes.end());
    double median;
    if (num_experiments % 2 == 0) {
        median = (free_zone_sizes[num_experiments / 2 - 1] +
            free_zone_sizes[num_experiments / 2]) / 2.0;
    }
    else {
        median = free_zone_sizes[num_experiments / 2];
    }

    return { mean, median, free_zone_sizes };
}