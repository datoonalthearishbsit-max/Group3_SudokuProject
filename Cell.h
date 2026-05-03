#ifndef CELL_H
#define CELL_H

#include <vector>
using namespace std;

class Cell {
private:
    int value;
    bool isFixed;

    vector<int> colHints;
    vector<int> rowHints;
    vector<int> boxHints;
    vector<int> consolidatedHints;

public:
    Cell();

    int getValue() const;
    bool getFixed() const;

    void setValue(int v);
    void setFixed(bool f);

    void setRowHints(vector<int> h);
    void setColHints(vector<int> h);
    void setBoxHints(vector<int> h);

    vector<int> getRowHints() const;
    vector<int> getColHints() const;
    vector<int> getBoxHints() const;
    vector<int> getConsolidatedHints() const;

    void refreshConsolidatedHints();
};
