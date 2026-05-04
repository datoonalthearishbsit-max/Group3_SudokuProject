#endif
#include "Cell.h"
#include <algorithm>

Cell::Cell() {
    value = 0;
    isFixed = false;
}

int Cell::getValue() const { return value; }
bool Cell::getFixed() const { return isFixed; }

void Cell::setValue(int v) { value = v; }
void Cell::setFixed(bool f) { isFixed = f; }

void Cell::setRowHints(vector<int> h) { rowHints = h; }
void Cell::setColHints(vector<int> h) { colHints = h; }
void Cell::setBoxHints(vector<int> h) { boxHints = h; }

vector<int> Cell::getRowHints() const { return rowHints; }
vector<int> Cell::getColHints() const { return colHints; }
vector<int> Cell::getBoxHints() const { return boxHints; }
vector<int> Cell::getConsolidatedHints() const { return consolidatedHints; }

void Cell::refreshConsolidatedHints() {
    consolidatedHints.clear();

    for (int x : rowHints) {
        if (find(colHints.begin(), colHints.end(), x) != colHints.end() &&
            find(boxHints.begin(), boxHints.end(), x) != boxHints.end()) {
            consolidatedHints.push_back(x);
        }
    }
}
