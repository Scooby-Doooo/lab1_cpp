#include "board.h"
#include <vector>
#include <set>
#include <algorithm>
#include "cell.h"

void Board::addNeighbors(const Cell& cell) {
    int directions[4][2] = {
        {-1, 0},  
        {1, 0},   
        {0, -1}, 
        {0, 1}   
    };
    
    for (int i = 0; i < 4; ++i) {
        int new_row = cell.row + directions[i][0];
        int new_col = cell.col + directions[i][1];
        
        if (new_row >= 0 && new_row < size && 
            new_col >= 0 && new_col < size) {
            neighbor_cells.insert(Cell(new_row, new_col));
        }
    }
}

Board::Board(int n) : size(n) {
    if (n <= 0) {
        throw std::invalid_argument("Board size must be positive");
    }
}

void Board::addSelectedCell(const Cell& cell) {
    if (cell.row < 0 || cell.row >= size || 
        cell.col < 0 || cell.col >= size) {
        throw std::out_of_range("Cell coordinates out of board bounds");
    }
    
    selected_cells.insert(cell);
    addNeighbors(cell);
}

int Board::calculateFreeZoneSize() const {
    int free_zone_size = 0;
    
    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            Cell current(row, col);
            if (selected_cells.find(current) == selected_cells.end() &&
                neighbor_cells.find(current) == neighbor_cells.end()) {
                ++free_zone_size;
            }
        }
    }
    
    return free_zone_size;
}

void Board::clear() {
    selected_cells.clear();
    neighbor_cells.clear();
}
