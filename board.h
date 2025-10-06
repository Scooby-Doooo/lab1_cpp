#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <set>
#include <algorithm>
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
    
    int calculateFreeZoneSize() const;
    
    void clear();
    
    int getSize() const { return size; }
    int getSelectedCount() const { return selected_cells.size(); }
};

#endif