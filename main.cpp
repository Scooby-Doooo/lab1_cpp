// Compiler: g++ 11.2.0 or higher with C++20 support
// Compilation command: g++ -std=c++20 -O2 main.cpp -o board_experiment

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include "random_cell_generator.h"
#include "board.h"
#include "experiment.h"

// Forward declaration
int getIntInput(const std::string& prompt, int min_val, int max_val);

void projectInfo()
{
    std::cout << "The project was completed by students of the K27 group, Dmytro Vivtonichenko and Yaroslav Kucher\n";
    std::cout << "A programme for exploring free zones on a square board\n";
    std::cout << "A compiler with C++20 support is used.\n\n";
}

void printMenu() {
    std::cout << "\n=== Exploring the free zone on a chessboard ===\n";
    std::cout << "1. Conduct an experiment for specific n and m\n";
    std::cout << "2. Investigate the dependence on m\n";
    std::cout << "3. Demonstration of the functional object's operation\n";
    std::cout << "4. Exit\n";
    std::cout << "Choose option: ";
}
void experiment1()
{
    int n = getIntInput("Enter board size n (from 1 to 500): ", 1, 500);
    std::string m_prompt = "Enter number of cells m (from 0 to " +
        std::to_string(n * n) + "): ";
    int m = getIntInput(m_prompt, 0, n * n);
    int num_exp = getIntInput("Enter number of experiments (from 100 to 10000): ",
        100, 10000);

    Experiment exp(n, num_exp);
    ExperimentResult result = exp.run(m);
    std::cout << "\n=== Experiment Results ===\n";
    std::cout << "Parameters: n=" << n << ", m=" << m << "\n";
    std::cout << "Number of experiments: " << num_exp << "\n";
    std::cout << "Total number of cells: " << n * n << "\n";
    std::cout << "Average free zone size: " << std::fixed
        << std::setprecision(2) << result.mean << "\n";
    std::cout << "Median free zone size: " << result.median << "\n";
    std::cout << "Free zone percentage: "
        << (result.mean / (n * n)) * 100 << "%\n";

    // Show distribution
    std::cout << "\nMin. free zone size: "
        << *std::min_element(result.free_zone_sizes.begin(),
            result.free_zone_sizes.end()) << "\n";
    std::cout << "Max. free zone size: "
        << *std::max_element(result.free_zone_sizes.begin(),
            result.free_zone_sizes.end()) << "\n";
}

void experiment2()
{
    int n = getIntInput("Enter board size n (from 1 to 50): ", 1, 50);
    std::string max_m_prompt = "Enter maximum m (from 1 to " +
        std::to_string(n * n) + "): ";
    int max_m = getIntInput(max_m_prompt, 1, n * n);
    std::string step_prompt = "Enter step for m (from 1 to " +
        std::to_string(max_m) + "): ";
    int step = getIntInput(step_prompt, 1, max_m);
    int num_exp = getIntInput("Enter number of experiments (from 100 to 5000): ",
        100, 5000);

    Experiment exp(n, num_exp);
    exp.analyzeMDependence(max_m, step);
}

void experiment3()
{
    std::cout << "\n=== Demonstration of functional object operation ===\n";
    int n = getIntInput("Enter board size n (from 1 to 500): ", 1, 500);
    RandomCellGenerator generator(n);

    std::string random_cells_prompt = "Enter number of random cells (from 1 to " +
        std::to_string(n * n) + "): ";
    int n_cells = getIntInput(random_cells_prompt, 1, n * n);
    std::cout << "Generating " << n_cells << " random cells:\n";
    for (int i = 0; i < n_cells; ++i) {
        Cell cell = generator();
        std::cout << "Cell " << (i + 1) << ": ("
            << cell.row << ", " << cell.col << ")\n";
    }
}

void endOfProgram()
{
    std::cout << "Program termination.\n";
}

void menuImplementation(int choice)
{
    switch (choice) {
        // Conducting a single experiment with specified parameters and displaying statistics
    case 1:
        experiment1();
        break;

    // Analyzing the dependency of free zone size on the number of occupied cells
    case 2:
        experiment2();
        break;

    // Demonstration of random cell coordinate generator operation
    case 3:
        experiment3();
        break;

    // Program termination
    case 4:
        endOfProgram();
        break;
    }
}

int getIntInput(const std::string& prompt, int min_val, int max_val) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= min_val && value <= max_val) {
            return value;
        }
        std::cout << "Incorrect input. Please try again.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int main() {
    try {
        projectInfo();
        
        while (true) {
            printMenu();
            int choice = getIntInput("", 1, 4);
            
            menuImplementation(choice);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 0;
    } catch (...) {
        std::cerr << "Unknown error" << std::endl;
        return 0;
    }
    
    return 0;
}