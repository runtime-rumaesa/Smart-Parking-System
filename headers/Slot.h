#ifndef SLOT_H
#define SLOT_H

#include <string>
#include <vector>  // ADD THIS LINE
using namespace std;

const int ROWS = 4;
const int COLS = 10;
const int MAX_SLOTS = ROWS * COLS;

class Slot {
public:
    int row, col;
    bool isOccupied;
    string licensePlate;

    Slot(int r = 0, int c = 0) {
        row = r;
        col = c;
        isOccupied = false;
        licensePlate = "";
    }
};

#endif // SLOT_H

