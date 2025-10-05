#ifndef RANDOM_CELL_GENERATOR_H
#define RANDOM_CELL_GENERATOR_H

#include <random>
#include <stdexcept>
#include "cell.h"

class RandomCellGenerator {

    int board_size;
    mutable std::mt19937 randomGenerator;
    mutable std::uniform_int_distribution<int> cellIndexDist;

public:
    RandomCellGenerator(int size, unsigned int seed = std::random_device{}())
        : board_size(size), randomGenerator(seed), cellIndexDist(0, size - 1) {
        if (size <= 0) {
            throw std::invalid_argument("Board size must be positive");
        }
    }

    Cell operator()() {
        return Cell(cellIndexDist(randomGenerator), cellIndexDist(randomGenerator));
    }

    int getBoardSize() {
        return board_size;
    }
};

#endif