# Smart Parking System

**C++ Smart Parking System with Qt Frontend**

---

## Overview
This project is a **Smart Parking System** implemented in **C++** using **Object-Oriented Programming** and a **Qt GUI frontend**.  
It efficiently manages parking slots, vehicle entry/exit, and a waiting queue when the parking is full.  
The system uses advanced data structures such as **linked lists**, **circular queues**, and **graphs (BFS)** for nearest slot allocation.

---

## Features
- Vehicle Entry & Exit
- Slot assignment using BFS (nearest to entrance)
- Linked List for parked vehicles
- Circular Queue for waiting vehicles
- Graph-based distance calculation
- Error handling for:
  - Removing non-existent vehicle
  - Parking full scenarios
- Qt GUI for real-time slot and vehicle visualization

---

## Project Structure

/Smart-Parking-System
│
├── src/ # C++ source files
├── include/ # Header files
├── resources/ # Qt resources (icons, images)
├── SmartParking.pro # Qt project file
├──  # Work Breakdown Structure
├──  # Test Cases
└── README.md # This file

---

## How to Run
1. Open `SmartParking.pro` in **Qt Creator**.
2. Build the project using your **C++ compiler** (MinGW/MSVC).
3. Run the application.
4. Use the GUI to:
   - Add vehicles
   - Remove vehicles
   - View parked slots and waiting queue

---

## Documentation


---

## Notes
- Billing functionality is **not implemented**; focus is on **parking management, data structures, and smart slot allocation**.
- All operations are handled **visually via Qt UI**.
- Test cases are included for verification of all functionalities.

---

