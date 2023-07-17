#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;

class SudokuGrid
{
    int grid[9][9];

public:
    SudokuGrid();
    bool isValid();
    bool solveGrid();
    void printGrid();
    bool usedInRow(int row, int num);
    bool usedInCol(int col, int num);
    bool usedInBox(int boxStartRow, int boxStartCol, int num);
    bool isSafe(int row, int col, int num);
    bool findEmptyCell(int &row, int &col);
};

SudokuGrid::SudokuGrid()
{
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
        // for (int i = 0; i < 9; i++)
        // {
        //     iss >> grid[i][0] >> grid[i][1] >> grid[i][2] >> grid[i][3] >> grid[i][4] >> grid[i][5] >> grid[i][6] >> grid[i][7] >> grid[i][8];
        // }
        lineCount++;
    }

    inputFile.close();

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

/* Returns a boolean which indicates whether
an assigned entry within the specified 3x3 box
matches the given number. */
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

/* Returns a boolean which indicates whether
an assigned entry in the specified row matches
the given number. */
bool SudokuGrid::usedInRow(int row, int num)
{
    for (int col = 0; col < 9; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}

/* Returns a boolean which indicates whether
an assigned entry in the specified column
matches the given number. */
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

    // If there is no unassigned location,
    // we are done
    if (!findEmptyCell(row, col))
        // success!
        return true;

    // Consider digits 1 to 9
    for (int num = 1; num <= 9; num++)
    {

        // Check if looks promising
        if (isSafe(row, col, num))
        {

            // Make tentative assignment
            grid[row][col] = num;

            // Return, if success
            if (solveGrid())
                return true;

            // Failure, unmake & try again
            grid[row][col] = 0;
        }
    }

    // This triggers backtracking
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

/* Returns a boolean which indicates whether
it will be legal to assign num to the given
row, col location. */
bool SudokuGrid::isSafe(int row,
                        int col, int num)
{
    /* Check if 'num' is not already placed in
    current row, current column
    and current 3x3 box */
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
                return false;
            }
            if (grid[i][j] < 0 || grid[i][j] > 9)
            {
                cout << "This grid is not valid. All values in the Sudoku must be between 1-9, with the exception of 0's in this grid as placeholders." << endl;
                return false;
            }
        }
    }

    if (count < 17)
    {
        cout << "This grid is not valid. A minimum of 17 givens are required to solve a grid." << endl;
        return false;
    }

    return true;
}

int main()
{
    int needsRules;
    cout << "Before you cheat at Sudoku, would you like to review the rules of sudoku? (Enter 1 for yes, 2 for no)" << endl;
    cin >> needsRules;
    while (needsRules != 1 && needsRules != 2)
    {
        cout << "Please enter 1 or 2!" << endl;
        cin >> needsRules;
    }
    printRules(needsRules);

    cout << "Ensure that you have pasted the grid correctly into the yourGrid.txt file" << endl;
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
        cout << "No solution exists for this grid, sorry :(";
    }

    return 0;
}