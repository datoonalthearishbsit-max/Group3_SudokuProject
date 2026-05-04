#ifndef SUDOKUBOARD_H
#define SUDOKUBOARD_H

#include "Cell.h"
#include <string>
#include <vector>
using namespace std;

class SudokuBoard {
private:
    Cell grid[9][9];
    int original[9][9];

public:
    SudokuBoard();

    void loadPuzzle();
    void resetBoard();
    void displayBoard();

    bool translate(string pos, int &r, int &c);

    vector<int> getMissingRow(int row);
    vector<int> getMissingCol(int col);
    vector<int> getMissingBox(int row, int col);

    void updateCellHints(int r, int c);
    void updateAllHints();
    void reactiveUpdate(int r, int c);

    void setCell(string pos, int val);
    void inspect(string pos);

    bool checkSolved();
};






















