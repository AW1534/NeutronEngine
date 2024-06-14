//
// Created by awilt on 18/12/22.
//

#include "Logger.h"
#include <QApplication>

#include "MainWindow.h"

int main(int argc, char *argv[]) {
    Logger::Log("Starting Neutron Editor");
    QApplication app(argc, argv);
    MainWindow mainWin;
    mainWin.show();
    app.setWindowIcon(QIcon(":/resources/branding/icon.png"));
    return app.exec();
}
