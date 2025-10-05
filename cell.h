#ifndef CELL_H
#define CELL_H

struct Cell {
    int row;
    int col;
    
    Cell(int r = 0, int c = 0);
    
    bool operator==(const Cell& other) const;
};

#endif
