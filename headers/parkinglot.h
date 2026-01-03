#ifndef PARKINGLOT_H
#define PARKINGLOT_H

#include "Slot.h"
#include "waitingqueue.h"
#include "graph.h"
#include <vector>
#include <fstream>
#include <iostream>
#include "parkedlist.h"
using namespace std;

class ParkingLot {
public:
    vector<vector<Slot>> parkingSlots;  // FIXED: 2D vector instead of 1D
    ParkedList parkedCars;
    WaitingQueue waitingQueue;
    Graph graph;

    ParkingLot();
    bool isPlateDuplicate(string plate);
    void loadData();
    void loadParkedVehicles();
    Slot* findNearestFreeSlot();
    void carEntry(string plate, bool handicapped);
    void carExit(string plate);
    void showParkedCars();
    void searchCar(string plate);
};

#endif // PARKINGLOT_H
