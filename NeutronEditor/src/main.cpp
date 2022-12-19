//
// Created by awilt on 18/12/22.
//

#include <Logger/Logger.h>
#include <QApplication>

#include "MainWindow.h"

int main(int argc, char *argv[]) {
    Logger::Log("Starting Neutron Editor");
    QApplication app(argc, argv);
    MainWindow mainWin;
    mainWin.show();
    return app.exec();
}
