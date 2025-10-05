#ifndef BOARD_H
#define BOARD_H

#include <set>
#include "cell.h"

class Board {
private:
    int size;
    std::set<Cell> selected_cells;
    std::set<Cell> neighbor_cells;  
    
    void addNeighbors(const Cell& cell);
    
public:
    Board(int n);
    void addSelectedCell(const Cell& cell);
    int getSize() const { return size; }
};

#endif
