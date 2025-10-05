#include "cell.h"

Cell::Cell(int r, int c) : row(r), col(c) {};

bool Cell::operator==(const Cell& other) const {
    return row == other.row && col == other.col;
}

bool Cell::operator<(const Cell& other) const {
    if (row != other.row) return row < other.row;
    return col < other.col;
}
