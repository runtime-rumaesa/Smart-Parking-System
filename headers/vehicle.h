#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include "Slot.h"
using namespace std;

class Vehicle {
public:
    string licensePlate;
    Slot* assignedSlot;
    Vehicle* next;
    bool isHandicapped;

    Vehicle() {
        licensePlate = "";
        assignedSlot = NULL;
        next = NULL;
        isHandicapped = false;
    }

    Vehicle(string plate, bool h) {
        licensePlate = plate;
        assignedSlot = NULL;
        next = NULL;
        isHandicapped = h;
    }

    bool isValidLicense(string plate) {
        int len = (int)plate.length();
        if (len == 7 && plate[3] == '-') {
            for (int i = 0; i < 3; i++)
                if (plate[i] < 'A' || plate[i] > 'Z') return false;
            for (int i = 4; i < 7; i++)
                if (plate[i] < '0' || plate[i] > '9') return false;
            return true;
        }
        if (len == 7 && plate[2] == '-') {
            for (int i = 0; i < 2; i++)
                if (plate[i] < 'A' || plate[i] > 'Z') return false;
            for (int i = 3; i < 7; i++)
                if (plate[i] < '0' || plate[i] > '9') return false;
            return true;
        }
        return false;
    }
};

#endif // VEHICLE_H
