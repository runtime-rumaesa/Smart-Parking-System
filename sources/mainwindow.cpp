
#include "Slot.h"
#include "parkinglot.h"
#include "mainwindow.h"


// Include ALL Qt headers we need
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QComboBox>
#include <QLabel>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <exception>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , parkingLot(new ParkingLot())
    , parkedTable(nullptr)
    , slotsGrid(nullptr)
    , waitingQueueText(nullptr)
    , plateInput(nullptr)
    , handicappedCombo(nullptr)
    , searchInput(nullptr)
    , removeInput(nullptr)
    , parkButton(nullptr)
    , removeButton(nullptr)
    , searchButton(nullptr)
    , controlGroup(nullptr)
    , parkedGroup(nullptr)
    , slotsGroup(nullptr)
    , waitingGroup(nullptr)
{
    setupUI();
    parkingLot->graph.bfsDistance(0, 0);
    parkingLot->loadData();
    refreshDisplay();
}

MainWindow::~MainWindow()
{
    delete parkingLot;
}

void MainWindow::setupUI()
{
    setWindowTitle("Smart Parking System");
    setMinimumSize(1200, 800);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);

    // Left panel
    QVBoxLayout* leftLayout = new QVBoxLayout();

    // Control Group
    controlGroup = new QGroupBox("Vehicle Operations", this);
    QGridLayout* controlLayout = new QGridLayout(controlGroup);

    controlLayout->addWidget(new QLabel("License Plate:"), 0, 0);
    plateInput = new QLineEdit();
    plateInput->setPlaceholderText("ABC-123 or AB-1234");
    controlLayout->addWidget(plateInput, 0, 1);

    controlLayout->addWidget(new QLabel("Handicapped:"), 1, 0);
    handicappedCombo = new QComboBox();
    handicappedCombo->addItem("No");
    handicappedCombo->addItem("Yes");
    controlLayout->addWidget(handicappedCombo, 1, 1);

    parkButton = new QPushButton("Park Vehicle");
    controlLayout->addWidget(parkButton, 2, 0, 1, 2);

    controlLayout->addWidget(new QLabel("Remove Vehicle:"), 3, 0);
    removeInput = new QLineEdit();
    controlLayout->addWidget(removeInput, 3, 1);

    removeButton = new QPushButton("Remove Vehicle");
    controlLayout->addWidget(removeButton, 4, 0, 1, 2);

    controlLayout->addWidget(new QLabel("Search Vehicle:"), 5, 0);
    searchInput = new QLineEdit();
    controlLayout->addWidget(searchInput, 5, 1);

    searchButton = new QPushButton("Search");
    controlLayout->addWidget(searchButton, 6, 0, 1, 2);

    leftLayout->addWidget(controlGroup);

    // Waiting Queue Group
    waitingGroup = new QGroupBox("Waiting Queue", this);
    waitingGroup->setMaximumHeight(200);
    QVBoxLayout* waitingLayout = new QVBoxLayout(waitingGroup);
    waitingQueueText = new QTextEdit();
    waitingQueueText->setReadOnly(true);
    waitingQueueText->setMaximumHeight(100);
    waitingLayout->addWidget(waitingQueueText);
    leftLayout->addWidget(waitingGroup);


    // Right panel
    QVBoxLayout* rightLayout = new QVBoxLayout();

    // Parked Vehicles Group
    parkedGroup = new QGroupBox("Parked Vehicles", this);
    QVBoxLayout* parkedLayout = new QVBoxLayout(parkedGroup);
    parkedTable = new QTableWidget();
    parkedTable->setColumnCount(4);
    QStringList headers;
    headers << "License Plate" << "Row" << "Column" << "Handicapped";
    parkedTable->setHorizontalHeaderLabels(headers);
    parkedTable->horizontalHeader()->setStretchLastSection(true);
    parkedLayout->addWidget(parkedTable);
    rightLayout->addWidget(parkedGroup);

    // Slots Grid Group
    slotsGroup = new QGroupBox("Parking Lot", this);
    QVBoxLayout* slotsLayout = new QVBoxLayout(slotsGroup);
    slotsGrid = new QTableWidget(4, 10);
    slotsGrid->setEditTriggers(QAbstractItemView::NoEditTriggers);
    slotsGrid->setSelectionMode(QAbstractItemView::NoSelection);

    // Make the table stretch to fill available space
    slotsGrid->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    slotsGrid->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    slotsLayout->addWidget(slotsGrid);
    rightLayout->addWidget(slotsGroup);
    // Combine layouts
    mainLayout->addLayout(leftLayout, 1);
    mainLayout->addLayout(rightLayout, 2);

    // Connect signals
    connect(parkButton, &QPushButton::clicked, this, &MainWindow::parkVehicle);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::removeVehicle);
    connect(searchButton, &QPushButton::clicked, this, &MainWindow::searchVehicle);

    connect(plateInput, &QLineEdit::returnPressed, this, &MainWindow::parkVehicle);
    connect(removeInput, &QLineEdit::returnPressed, this, &MainWindow::removeVehicle);
    connect(searchInput, &QLineEdit::returnPressed, this, &MainWindow::searchVehicle);
}

void MainWindow::parkVehicle()
{
    QString plate = plateInput->text().trimmed().toUpper();
    bool handicapped = (handicappedCombo->currentIndex() == 1);

    if (plate.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a license plate.");
        return;
    }

    // Validate license plate format
    Vehicle tempVehicle;
    if (!tempVehicle.isValidLicense(plate.toStdString())) {
        QMessageBox::warning(this, "Invalid License",
                             "Invalid license format! Use ABC-123 or AB-1234");
        return;
    }

    // Check for duplicate
    if (parkingLot->isPlateDuplicate(plate.toStdString())) {
        QMessageBox::warning(this, "Duplicate License",
                             "License plate " + plate + " already exists in the system!");
        return;
    }

    try {
        parkingLot->carEntry(plate.toStdString(), handicapped);
        plateInput->clear();
        refreshDisplay();
        QMessageBox::information(this, "Success", "Vehicle processed successfully");
    } catch (...) {
        QMessageBox::critical(this, "Error", "An error occurred");
    }
}

void MainWindow::removeVehicle()
{
    QString plate = removeInput->text().trimmed().toUpper();

    if (plate.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a license plate to remove.");
        return;
    }

    // Validate license plate format
    Vehicle tempVehicle;
    if (!tempVehicle.isValidLicense(plate.toStdString())) {
        QMessageBox::warning(this, "Invalid License",
                             "Invalid license format! Use ABC-123 or AB-1234");
        return;
    }

    // Check if vehicle exists
    if (!parkingLot->isPlateDuplicate(plate.toStdString())) {
        QMessageBox::warning(this, "Vehicle Not Found",
                             "License plate " + plate + " is not in the system!");
        return;
    }

    try {
        parkingLot->carExit(plate.toStdString());
        removeInput->clear();
        refreshDisplay();
        QMessageBox::information(this, "Success", "Vehicle removed successfully");
    } catch (...) {
        QMessageBox::critical(this, "Error", "An error occurred");
    }
}

void MainWindow::searchVehicle()
{
    QString plate = searchInput->text().trimmed().toUpper();

    if (plate.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a license plate to search.");
        return;
    }

    // Validate license plate format
    Vehicle tempVehicle;
    if (!tempVehicle.isValidLicense(plate.toStdString())) {
        QMessageBox::warning(this, "Invalid License",
                             "Invalid license format! Use ABC-123 or AB-1234");
        return;
    }

    try {
        std::string plateStr = plate.toStdString();
        bool found = false;
        QString message;

        // Search in parked vehicles
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (parkingLot->parkingSlots[i][j].isOccupied &&
                    parkingLot->parkingSlots[i][j].licensePlate == plateStr) {
                    message = QString("Vehicle found in Parking Lot!\n\n"
                                      "License Plate: %1\n"
                                      "Slot Location: (%2, %3)")
                                  .arg(plate)
                                  .arg(i)
                                  .arg(j);
                    found = true;
                    break;
                }
            }
            if (found) break;
        }

        // Search in waiting queue
        if (!found && parkingLot->waitingQueue.plateExists(plateStr)) {
            message = QString("Vehicle found in Waiting Queue!\n\n"
                              "License Plate: %1")
                          .arg(plate);
            found = true;
        }

        if (!found) {
            message = QString("Vehicle not found in the system!\n\n"
                              "License Plate: %1")
                          .arg(plate);
        }

        QMessageBox::information(this, "Search Result", message);
        searchInput->clear();
    } catch (...) {
        QMessageBox::critical(this, "Error", "An error occurred");
    }
}

void MainWindow::refreshDisplay()
{
    updateParkedTable();
    updateWaitingQueue();
    updateSlotsGrid();
}

void MainWindow::updateParkedTable()
{
    parkedTable->setRowCount(0);

    Vehicle* current = parkingLot->parkedCars.head;
    int row = 0;

    while (current != nullptr) {
        parkedTable->insertRow(row);

        parkedTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(current->licensePlate)));

        if (current->assignedSlot != nullptr) {
            parkedTable->setItem(row, 1, new QTableWidgetItem(QString::number(current->assignedSlot->row)));
            parkedTable->setItem(row, 2, new QTableWidgetItem(QString::number(current->assignedSlot->col)));
        } else {
            parkedTable->setItem(row, 1, new QTableWidgetItem("N/A"));
            parkedTable->setItem(row, 2, new QTableWidgetItem("N/A"));
        }

        parkedTable->setItem(row, 3, new QTableWidgetItem(current->isHandicapped ? "Yes" : "No"));

        current = current->next;
        row++;
    }
}

void MainWindow::updateWaitingQueue()
{
    if (parkingLot->waitingQueue.isEmpty()) {
        waitingQueueText->setText("Waiting queue is empty.");
    } else {
        QString queueText = "Waiting Queue (Handicapped Priority):\n\n";
        for (int i = 0; i < parkingLot->waitingQueue.size; i++) {
            QString plate = QString::fromStdString(parkingLot->waitingQueue.arr[i].licensePlate);
            QString handicapped = parkingLot->waitingQueue.arr[i].isHandicapped ? " (Handicapped)" : "";
            queueText += QString::number(i + 1) + ". " + plate + handicapped + "\n";
        }
        waitingQueueText->setText(queueText);
    }
}
void MainWindow::updateSlotsGrid()
{
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            QTableWidgetItem* item = new QTableWidgetItem();

            Slot& slotPtr = parkingLot->parkingSlots[i][j];

            if (slotPtr.isOccupied) {
                item->setBackground(Qt::red);
                item->setText(QString::fromStdString(slotPtr.licensePlate));
                item->setForeground(Qt::white);
            } else {
                item->setBackground(Qt::green);
                item->setText("Free");
            }

            item->setTextAlignment(Qt::AlignCenter);
            slotsGrid->setItem(i, j, item);
        }
    }
}
