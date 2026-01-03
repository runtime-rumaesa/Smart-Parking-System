#include "parkinglot.h"

ParkingLot::ParkingLot() {
    // Initialize 2D vector with proper dimensions
    parkingSlots.resize(ROWS);
    for (int i = 0; i < ROWS; i++) {
        parkingSlots[i].resize(COLS); // Correctly resizes the inner vector
        for (int j = 0; j < COLS; j++) {
            parkingSlots[i][j] = Slot(i, j);
        }
    }
}

bool ParkingLot::isPlateDuplicate(string plate) {
    if (parkedCars.plateExists(plate)) {
        return true;
    }
    if (waitingQueue.plateExists(plate)) {
        return true;
    }
    return false;
}

void ParkingLot::loadData() {
    loadParkedVehicles();
    waitingQueue.loadFromFile();
}

void ParkingLot::loadParkedVehicles() {
    ifstream fin(parkedCars.FILE_NAME);
    if (!fin) return;

    string plate;
    int r, c;
    bool handicapped;
    int temp_handicapped;

    while (fin >> plate >> r >> c >> temp_handicapped) {
        handicapped = (temp_handicapped == 1);
        if (r < 0 || r >= ROWS || c < 0 || c >= COLS) {
            continue;
        }
        // Access 2D vector properly
        parkingSlots[r][c].isOccupied = true;
        parkingSlots[r][c].licensePlate = plate;

        Vehicle* v = new Vehicle(plate, handicapped);
        v->assignedSlot = &parkingSlots[r][c];
        parkedCars.addVehicle(v, false);
    }
    fin.close();
}

Slot* ParkingLot::findNearestFreeSlot() {
    int minDist = 1e9;
    Slot* nearest = NULL;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int dis = graph.dist[i][j];
            if (!parkingSlots[i][j].isOccupied && dis != -1) {
                if (dis < minDist) {
                    minDist = dis;
                    nearest = &parkingSlots[i][j];
                }
            }
        }
    }
    return nearest;
}

void ParkingLot::carEntry(string plate, bool handicapped) {
    Vehicle tempVehicle(plate, handicapped);

    if (isPlateDuplicate(plate)) {
        cout << "Error: License plate " << plate << " already exists in the system!\n";
        return;
    }

    if (!tempVehicle.isValidLicense(plate)) {
        cout << "Invalid license format! Use ABC-123 or AB-1234\n";
        return;
    }

    Slot* freeSlot = findNearestFreeSlot();

    if (freeSlot != NULL) {
        freeSlot->isOccupied = true;
        freeSlot->licensePlate = plate;
        Vehicle* v = new Vehicle(plate, handicapped);
        v->assignedSlot = freeSlot;
        parkedCars.addVehicle(v);
        cout << "Vehicle parked at slot (" << freeSlot->row << "," << freeSlot->col << ")\n";
    } else {
        cout << "Parking lot full. Vehicle added to waiting queue.\n";
        waitingQueue.enqueue(tempVehicle);
    }
}

void ParkingLot::carExit(string plate) {
    Vehicle* temp = parkedCars.head;
    Slot* slotToFree = NULL;
    while (temp != NULL) {
        if (temp->licensePlate == plate) {
            slotToFree = temp->assignedSlot;
            break;
        }
        temp = temp->next;
    }

    if (slotToFree == NULL) {
        cout << "Vehicle not found in parked list.\n";
        return;
    }

    slotToFree->isOccupied = false;
    slotToFree->licensePlate = "";
    parkedCars.removeVehicle(plate);
    cout << "Slot (" << slotToFree->row << "," << slotToFree->col << ") is now free.\n";

    if (!waitingQueue.isEmpty()) {
        Vehicle nextCar = waitingQueue.dequeue();
        cout << "Attempting to park priority vehicle " << nextCar.licensePlate << " from waiting queue...\n";
        carEntry(nextCar.licensePlate, nextCar.isHandicapped);
    }
}

void ParkingLot::showParkedCars() {
    parkedCars.display();
}

void ParkingLot::searchCar(string plate) {
    bool found = false;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (parkingSlots[i][j].isOccupied && parkingSlots[i][j].licensePlate == plate) {
                cout << "\nVehicle found in Parking Lot!";
                cout << "\nLicense Plate: " << plate;
                cout << "\nSlot Location: (" << parkingSlots[i][j].row << ", " << parkingSlots[i][j].col << ")\n";
                found = true;
                break;
            }
        }
        if (found) break;
    }
    if (found) return;

    if (waitingQueue.plateExists(plate)) {
        cout << "\nVehicle found in Waiting Queue!";
        cout << "\nLicense Plate: " << plate << endl;
        found = true;
    }

    if (!found) cout << "\nVehicle not found in the parking system.\n";
}
