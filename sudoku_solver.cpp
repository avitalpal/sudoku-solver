#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath> // needed for floor function to check if the grid entries are all integers
using namespace std;

#define error "Please ensure that you have pasted the grid correctly into the `yourGrid.txt` file."

// SudokuGrid is a class that holds the Sudoku grid layout provided in yourGrid.txt, a constructor, and member functions for validation and solving
// The main object in this program is userGrid
class SudokuGrid
{
    int grid[9][9];

public:
    SudokuGrid();

    // Check that the grid is valid and solvable by comparing each grid value to specific conditions
    bool isValid();
    // Finds solution and calls other functions to evaluate the grid
    bool solveGrid();
    // Displays the grid to the user
    void printGrid();
    // Checks if a potential grid entry is already used in a grid row
    bool usedInRow(int row, int num);
    // Checks if a potential grid entry is already used in a grid column
    bool usedInCol(int col, int num);
    // Checks if a potential grid entry is already used in a 3x3 box
    bool usedInBox(int boxStartRow, int boxStartCol, int num);
    // Checks if adding an entry will be fatal to the solution
    bool isSafe(int row, int col, int num);
    // Locates grid cells containing 0's, indicating they are empty and must be solved
    bool findEmptyCell(int &row, int &col);
};

SudokuGrid::SudokuGrid()
{
    // Reading the file and inputting it into the grid object
    ifstream inputFile("yourGrid.txt");
    string line;

    if (!inputFile)
    {
        cerr << "Failed to open file." << endl;
        return;
    }

    int lineCount = 0;
    while (getline(inputFile, line))
    {
        istringstream iss(line);
        iss >> grid[lineCount][0] >> grid[lineCount][1] >> grid[lineCount][2] >> grid[lineCount][3] >> grid[lineCount][4] >> grid[lineCount][5] >> grid[lineCount][6] >> grid[lineCount][7] >> grid[lineCount][8];
        lineCount++;
    }

    inputFile.close();

    // Outputting the grid for user display
    cout << "Your entered grid:" << endl;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    return;
}

bool SudokuGrid::usedInBox(int boxStartRow,
                           int boxStartCol, int num)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row + boxStartRow]
                    [col + boxStartCol] ==
                num)
                return true;
    return false;
}

bool SudokuGrid::usedInRow(int row, int num)
{
    for (int col = 0; col < 9; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}

bool SudokuGrid::usedInCol(int col, int num)
{
    for (int row = 0; row < 9; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}

bool SudokuGrid::solveGrid()
{
    int row, col;

    // If there is no unassigned location, we're done
    if (!findEmptyCell(row, col))
        // success!
        return true;

    // Consider digits 1 to 9
    for (int num = 1; num <= 9; num++)
    {

        // Check if it looks promising
        if (isSafe(row, col, num))
        {

            // Make tentative assignment
            grid[row][col] = num;

            // Return, if success
            if (solveGrid())
                return true;

            // Failure, undo & try again
            grid[row][col] = 0;
        }
    }

    // This triggers backtracking in case of multiple solutions
    return false;
}

void SudokuGrid::printGrid()
{
    cout << "Solved Sudoku:" << endl;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

bool SudokuGrid::isSafe(int row,
                        int col, int num)
{
    // Check if the potential number is not already placed in a row/column/box
    return !usedInRow(row, num) && !usedInCol(col, num) && !usedInBox(row - row % 3, col - col % 3, num) && grid[row][col] == 0;
}

bool SudokuGrid::findEmptyCell(int &row, int &col)
{
    for (row = 0; row < 9; row++)
        for (col = 0; col < 9; col++)
            if (grid[row][col] == 00)
                return true;
    return false;
}

// In case the user needs clarification on how sudoku works
void printRules(int needsRules)
{
    if (needsRules == 1)
    {
        cout << "The rules of Sudoku are as such:" << endl;
        cout << "1. The game board is made up of 9*9 boxes, organized into 9 3*3 squares" << endl;
        cout << "2. The game will display the grid with some of the boxes already filled with random numbers ranging from 1-9" << endl;
        cout << "3. You, as the player, will be able to fill in the empty boxes" << endl;
        cout << "4. You may not repeat any number in any column, row, or square" << endl;
        cout << "5. If you fill in the boxes with the correct numbers and without repetition, you win the game" << endl;
    }
    else if (needsRules == 2)
    {
        return;
    }
}

bool SudokuGrid::isValid()
{
    int rows = sizeof(grid) / sizeof(grid[0]);
    int cols = sizeof(grid[0]) / sizeof(grid[0][0]);
    if (rows != 9 || cols != 9)
    {
        cout << "This grid is not valid. It must have exactly 9 rows and 9 columns." << endl;
        return false;
    }

    int count = 0;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (grid[i][j] != 0)
            {
                count++;
            }
            if (floor(grid[i][j]) != grid[i][j])
            {
                cout << "This grid is not valid. All values in the Sudoku must be positive integers." << endl;
                cout << error << endl;
                return false;
            }
            if (grid[i][j] < 0 || grid[i][j] > 9)
            {
                cout << "This grid is not valid. All values in the Sudoku must be between 1-9, with the exception of 0's in this grid as placeholders." << endl;
                cout << error << endl;
                return false;
            }
        }
    }

    if (count < 17)
    {
        cout << "This grid is not valid. A minimum of 17 givens are required to solve a grid." << endl;
        cout << error << endl;
        return false;
    }

    return true;
}

int main()
{
    int needsRules;
    cout << "Before you cheat at Sudoku, would you like to review the rules of the game? (Enter 1 for yes, 2 for no)" << endl;
    cin >> needsRules;
    while (needsRules != 1 && needsRules != 2)
    {
        cout << "Please enter 1 or 2!" << endl;
        cin >> needsRules;
    }
    printRules(needsRules);

    SudokuGrid userGrid;

    if (userGrid.isValid() == false)
    {
        return 0;
    }

    if (userGrid.solveGrid() == true)
    {
        userGrid.printGrid();
    }
    else
    {
        cout << "No solution exists for this grid, sorry :(" << endl;
        cout << error << endl;
    }

    return 0;
}