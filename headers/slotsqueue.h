#ifndef SLOTSQUEUE_H
#define SLOTSQUEUE_H

// Simple struct/class to hold a slot coordinate
class SlotCoords {
public:
    int r, c;

    // FIX 1: ADD THE REQUIRED DEFAULT CONSTRUCTOR
    SlotCoords() : r(0), c(0) {} // Resolves 'no matching function' and 'must explicitly initialize' errors

    // 2. Existing parameterized constructor
    SlotCoords(int row, int col) : r(row), c(col) {}
};

// Simple Queue implementation for BFS
class SlotsQueue {
private:
    SlotCoords arr[100];
    int front, rear, size;
public:
    SlotsQueue() : front(0), rear(-1), size(0) {}

    bool isEmpty() const { return size == 0; }
    bool isFull() const { return size == 100; }

    void enqueue(int r, int c) {
        if (isFull()) return;
        rear = (rear + 1) % 100;
        arr[rear] = SlotCoords(r, c);
        size++;
    }

    void dequeue(int& r, int& c) {
        if (isEmpty()) return;
        r = arr[front].r;
        c = arr[front].c;
        front = (front + 1) % 100;
        size--;
    }
}; // <-- Semicolon is present here

#endif // SLOTSQUEUE_H
