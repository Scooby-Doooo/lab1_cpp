#include "board.h"
#include <stdexcept>

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
}
