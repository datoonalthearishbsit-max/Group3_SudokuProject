#endif
#include "SudokuBoard.h"
#include <iostream>
#include <cctype>
#include <algorithm>

using namespace std;

SudokuBoard::SudokuBoard() {
    loadPuzzle();
}

void SudokuBoard::loadPuzzle() {
    int puzzle[9][9] = {
        {5,3,0,0,7,0,0,0,0},
        {6,0,0,1,9,5,0,0,0},
        {0,9,8,0,0,0,0,6,0},
        {8,0,0,0,6,0,0,0,3},
        {4,0,0,8,0,3,0,0,1},
        {7,0,0,0,2,0,0,0,6},
        {0,6,0,0,0,0,2,8,0},
        {0,0,0,4,1,9,0,0,5},
        {0,0,0,0,8,0,0,7,9}
    };

    for (int r = 0; r < 9; r++)
        for (int c = 0; c < 9; c++) {
            grid[r][c].setValue(puzzle[r][c]);
            original[r][c] = puzzle[r][c];
            grid[r][c].setFixed(puzzle[r][c] != 0);
        }

    updateAllHints();
}

void SudokuBoard::resetBoard() {
    for (int r = 0; r < 9; r++)
        for (int c = 0; c < 9; c++)
            grid[r][c].setValue(original[r][c]);

    updateAllHints();
}

void SudokuBoard::displayBoard() {
    cout << "\n    1 2 3   4 5 6   7 8 9\n";
    for (int r = 0; r < 9; r++) {
        if (r % 3 == 0) cout << "  +-------+-------+-------+\n";
        cout << char('A' + r) << " | ";
        for (int c = 0; c < 9; c++) {
            if (grid[r][c].getValue() == 0) cout << ". ";
            else cout << grid[r][c].getValue() << " ";
            if ((c + 1) % 3 == 0) cout << "| ";
        }
        cout << endl;
    }
    cout << "  +-------+-------+-------+\n";
}

bool SudokuBoard::translate(string pos, int &r, int &c) {
    if (pos.size() != 2) return false;
    r = toupper(pos[0]) - 'A';
    c = pos[1] - '1';
    return r >= 0 && r < 9 && c >= 0 && c < 9;
}

vector<int> SudokuBoard::getMissingRow(int row) {
    vector<bool> used(10,false);
    for (int c=0;c<9;c++) used[grid[row][c].getValue()] = true;

    vector<int> res;
    for (int i=1;i<=9;i++) if(!used[i]) res.push_back(i);
    return res;
}

vector<int> SudokuBoard::getMissingCol(int col) {
    vector<bool> used(10,false);
    for (int r=0;r<9;r++) used[grid[r][col].getValue()] = true;

    vector<int> res;
    for (int i=1;i<=9;i++) if(!used[i]) res.push_back(i);
    return res;
}

vector<int> SudokuBoard::getMissingBox(int row,int col) {
    vector<bool> used(10,false);
    int sr=(row/3)*3, sc=(col/3)*3;

    for(int r=sr;r<sr+3;r++)
        for(int c=sc;c<sc+3;c++)
            used[grid[r][c].getValue()] = true;

    vector<int> res;
    for(int i=1;i<=9;i++) if(!used[i]) res.push_back(i);
    return res;
}

void SudokuBoard::updateCellHints(int r,int c){
    if(grid[r][c].getValue()!=0) return;
    grid[r][c].setRowHints(getMissingRow(r));
    grid[r][c].setColHints(getMissingCol(c));
    grid[r][c].setBoxHints(getMissingBox(r,c));
    grid[r][c].refreshConsolidatedHints();
}

void SudokuBoard::updateAllHints(){
    for(int r=0;r<9;r++)
        for(int c=0;c<9;c++)
            updateCellHints(r,c);
}

void SudokuBoard::reactiveUpdate(int r,int c){
    for(int i=0;i<9;i++){
        updateCellHints(r,i);
        updateCellHints(i,c);
    }
}

void SudokuBoard::setCell(string pos,int val){
    int r,c;
    if(!translate(pos,r,c)) return;
    if(grid[r][c].getFixed()) return;
    grid[r][c].setValue(val);
    reactiveUpdate(r,c);
}

void SudokuBoard::inspect(string pos){
    int r,c;
    if(!translate(pos,r,c)) return;

    cout<<"\nHints: ";
    for(int x:grid[r][c].getConsolidatedHints())
        cout<<x<<" ";
    cout<<endl;
}

bool SudokuBoard::checkSolved(){
    for(int r=0;r<9;r++)
        for(int c=0;c<9;c++)
            if(grid[r][c].getValue()==0) return false;
    return true;
}


