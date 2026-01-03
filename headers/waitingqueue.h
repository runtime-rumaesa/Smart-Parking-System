#ifndef WAITINGQUEUE_H
#define WAITINGQUEUE_H

#include "vehicle.h"
#include <fstream>
#include <iostream>
using namespace std;

const int IGNORE_MAX = 10000;

class WaitingQueue {
public:
    Vehicle arr[10];
    int front, rear, size;
    const string FILE_NAME = "waiting_vehicles.txt";

    WaitingQueue() { front = 0; rear = -1; size = 0; }

    bool isFull() { return size == 10; }
    bool isEmpty() { return size == 0; }

    bool plateExists(string plate) {
        for (int i = 0; i < size; i++) {
            if (arr[i].licensePlate == plate) {
                return true;
            }
        }
        return false;
    }

    void saveToFile() {
        ofstream fout(FILE_NAME);
        if (!fout) {
            cout << "Error opening file for writing: " << FILE_NAME << endl;
            return;
        }
        for (int i = 0; i < size; i++) {
            fout << arr[i].licensePlate << " " << arr[i].isHandicapped << endl;
        }
        fout.close();
    }

    void loadFromFile() {
        ifstream fin(FILE_NAME);
        if (!fin) return;

        string tempPlates[10];
        int tempHandicapped[10];
        int tempCount = 0;

        string plate;
        int temp_handicapped;

        while (fin >> plate >> temp_handicapped && tempCount < 10) {
            tempPlates[tempCount] = plate;
            tempHandicapped[tempCount] = temp_handicapped;
            tempCount++;
        }
        fin.close();

        front = 0; rear = -1; size = 0;

        for (int k = 0; k < tempCount; k++) {
            Vehicle v(tempPlates[k], (tempHandicapped[k] == 1));

            if (v.isHandicapped) {
                int insertionIndex = 0;

                for (int i = 0; i < size; i++) {
                    if (arr[i].isHandicapped) {
                        insertionIndex = i + 1;
                    } else {
                        break;
                    }
                }

                for (int i = size; i > insertionIndex; i--) arr[i] = arr[i - 1];
                arr[insertionIndex] = v;
                rear++;
            } else {
                rear++;
                arr[rear] = v;
            }
            size++;
        }
    }

    void enqueue(Vehicle v) {
        if (isFull()) {
            cout << "Waiting queue is full! Cannot add " << v.licensePlate << endl;
            return;
        }

        if (v.isHandicapped) {
            int insertionIndex = 0;

            for (int i = 0; i < size; i++) {
                if (arr[i].isHandicapped) {
                    insertionIndex = i + 1;
                } else {
                    break;
                }
            }

            for (int i = size; i > insertionIndex; i--) arr[i] = arr[i - 1];

            arr[insertionIndex] = v;
            rear++;
        } else {
            rear++;
            arr[rear] = v;
        }

        size++;
        cout << "Vehicle " << v.licensePlate
             << (v.isHandicapped ? " (Handicapped)" : "")
             << " added to waiting queue.\n";

        saveToFile();
    }

    Vehicle dequeue() {
        if (isEmpty()) {
            return Vehicle("", false);
        }
        Vehicle v = arr[0];
        for (int i = 0; i < size - 1; i++) arr[i] = arr[i + 1];
        rear--;
        size--;
        cout << "Vehicle " << v.licensePlate << " removed from waiting queue.\n";

        saveToFile();

        return v;
    }

    void display() {
        if (isEmpty()) {
            cout << "Waiting queue is empty.\n";
            return;
        }
        cout << "\n--- Waiting Queue (Handicapped Priority) ---\n";
        for (int i = 0; i < size; i++) {
            cout << i + 1 << ". " << arr[i].licensePlate;
            if (arr[i].isHandicapped) cout << " (Handicapped)";
            cout << endl;
        }
    }
};

#endif // WAITINGQUEUE_H
