#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Forward declarations only - no includes that might cause template issues
class QTableWidget;
class QLineEdit;
class QPushButton;
class QTextEdit;
class QComboBox;
class QLabel;
class QGroupBox;
class QVBoxLayout;
class QHBoxLayout;
class ParkingLot;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void parkVehicle();
    void removeVehicle();
    void searchVehicle();
    void refreshDisplay();

private:
    void setupUI();
    void updateParkedTable();
    void updateWaitingQueue();
    void updateSlotsGrid();

    ParkingLot* parkingLot;

    QTableWidget* parkedTable;
    QTableWidget* slotsGrid;
    QTextEdit* waitingQueueText;

    QLineEdit* plateInput;
    QComboBox* handicappedCombo;
    QLineEdit* searchInput;
    QLineEdit* removeInput;

    QPushButton* parkButton;
    QPushButton* removeButton;
    QPushButton* searchButton;
    QPushButton* refreshButton;

    QGroupBox* controlGroup;
    QGroupBox* parkedGroup;
    QGroupBox* slotsGroup;
    QGroupBox* waitingGroup;
};

#endif
