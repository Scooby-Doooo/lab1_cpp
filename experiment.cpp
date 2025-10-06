#include "experiment.h"
#include <iostream>
#include <format>
#include <algorithm>
#include <stdexcept>
#include "board.h"
#include "random_cell_generator.h"

Experiment::Experiment(int n, int experiments)
    : board_size(n), num_experiments(experiments) {
    if (n <= 0 || experiments <= 0) {
        throw std::invalid_argument("Invalid experiment parameters");
    }
}

ExperimentResult Experiment::run(int m) const {
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

void Experiment::analyzeMDependence(int max_m, int step) const {
    std::cout << "\n=== Analysis of free zone size dependence on m ===\n";
    std::cout << "Board size: " << board_size << "x" << board_size << "\n";
    std::cout << "Number of experiments for each m: " << num_experiments << "\n\n";

    std::cout << std::format("{:>10} {:>15} {:>15} {:>15} {:>20}\n",
        "m", "m/(n^2)", "Average", "Median", "% free zone");
    for (int i = 0; i < 75; ++i) std::cout << '-';
    std::cout << "\n";

    for (int m = 0; m <= max_m; m += step) {
        ExperimentResult result = run(m);
        double percent_free = (result.mean / (board_size * board_size)) * 100;

        std::cout << std::format("{:>10} {:>15.2f} {:>15.2f} {:>15.2f} {:>18.1f}%\n",
            m,
            static_cast<double>(m) / (board_size * board_size),
            result.mean,
            result.median,
            percent_free);
    }
}
