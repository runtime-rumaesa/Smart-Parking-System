#ifndef GRAPH_H
#define GRAPH_H

#include "Slot.h" // Includes ROWS (4) and COLS (10)

class SlotsQueue; // Forward declaration

class Graph {
private:
    // Helper function for BFS
    void bfs(int startR, int startC);

public:
    // This is the array used in mainwindow.cpp line 303 and ParkingLot.cpp
    // ROWS=4, COLS=10 from Slot.h
    int dist[ROWS][COLS];

    Graph(); // Constructor to initialize dist array

    // Computes and stores the distance from a starting slot (e.g., entrance)
    void bfsDistance(int startR, int startC);
};

#endif // GRAPH_H
