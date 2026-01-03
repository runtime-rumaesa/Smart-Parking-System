#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setApplicationName("Smart Parking System");
    app.setApplicationVersion("1.0");
    app.setOrganizationName("ParkingSystem");

    MainWindow window;
    window.show();

    return app.exec();
}
