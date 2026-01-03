#ifndef PARKEDLIST_H
#define PARKEDLIST_H

#include "vehicle.h"
#include <fstream>
#include <iostream>
using namespace std;

class ParkedList {
public:
    Vehicle *head, *tail;
    const string FILE_NAME = "parked_vehicles.txt";

    ParkedList() { head = tail = NULL; }

    bool isEmpty() { return head == NULL; }

    bool plateExists(string plate) {
        Vehicle *temp = head;
        while (temp != NULL) {
            if (temp->licensePlate == plate) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void display() {
        if (isEmpty()) {
            cout << "No vehicles are currently parked.\n";
            return;
        }
        Vehicle *temp = head;
        cout << "\n--- Parked Vehicles ---\n";
        while (temp != NULL) {
            cout << "Plate: " << temp->licensePlate;
            if (temp->assignedSlot != NULL)
                cout << " | Slot: (" << temp->assignedSlot->row << "," << temp->assignedSlot->col << ")";
            cout << (temp->isHandicapped ? " (Handicapped)" : "") << endl;
            temp = temp->next;
        }
    }

    void saveToFile() {
        ofstream fout(FILE_NAME);
        if (!fout) {
            cout << "Error opening file for writing: " << FILE_NAME << endl;
            return;
        }
        Vehicle *temp = head;
        while (temp != NULL) {
            int r = (temp->assignedSlot != NULL) ? temp->assignedSlot->row : -1;
            int c = (temp->assignedSlot != NULL) ? temp->assignedSlot->col : -1;
            fout << temp->licensePlate << " "
                 << r << " "
                 << c << " "
                 << temp->isHandicapped << endl;
            temp = temp->next;
        }
        fout.close();
    }

    void addVehicle(Vehicle* v, bool save = true) {
        v->next = NULL;

        if (head == NULL) head = tail = v;
        else { tail->next = v; tail = v; }

        if (save) {
            cout << "Vehicle " << v->licensePlate << " parked successfully.\n";
        }

        if (save) saveToFile();
    }

    void removeVehicle(string plate) {
        if (isEmpty()) {
            cout << "No vehicles parked.\n";
            return;
        }
        Vehicle *curr = head, *prev = NULL;
        while (curr != NULL && curr->licensePlate != plate) {
            prev = curr;
            curr = curr->next;
        }
        if (curr == NULL) {
            cout << "Vehicle with plate " << plate << " not found.\n";
            return;
        }
        if (curr == head) head = head->next;
        else prev->next = curr->next;

        if (curr == tail) {
            tail = prev;
        }

        cout << "Vehicle " << plate << " removed successfully.\n";
        delete curr;
        saveToFile();
    }
}; // <-- CRITICAL FIX: Semicolon added

#endif // PARKEDLIST_H
