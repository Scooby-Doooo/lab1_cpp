#include <iostream>
#include "board.h"
#include "cell.h"

void printMenu() {
    std::cout << "\n=== Board Experiment Program ===\n";
    std::cout << "1. Run experiment\n";
    std::cout << "2. Exit\n";
    std::cout << "Choose option: ";
}

int main() {
    std::cout << "Board Free Zone Explorer\n";
    
    while (true) {
        printMenu();
        int choice;
        std::cin >> choice; 
        
        if (choice == 1) {
            int n, m;
            std::cout << "Enter board size: ";
            std::cin >> n; 
            std::cout << "Enter number of cells: ";
            std::cin >> m;
            
            Board board(n);
            std::cout << "Board created with size " << n << "x" << n << "\n";
            
        } else if (choice == 2) {
            std::cout << "Exiting...\n";
            break;
        }
    }
    
    return 0;
}
