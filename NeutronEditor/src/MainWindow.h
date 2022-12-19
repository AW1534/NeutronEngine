//
// Created by awilt on 18/12/22.
//

#ifndef NEUTRONEDITOR_MAINWINDOW_H
#define NEUTRONEDITOR_MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QAction;
class QListWidget;
class QMenu;
class QTextEdit;
QT_END_NAMESPACE

enum State {
    STATE_STOPPED,
    STATE_PLAYING,
    STATE_PAUSED
};

//! [0]
class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow();
    State state;

private slots:
    void newLetter();
    void save();
    void print();
    void undo();
    void about();
    void insertCustomer(const QString &customer);
    void addParagraph(const QString &paragraph);

private:
    void createActions();
    void createStatusBar();
    void createDockWindows();

    QTextEdit *textEdit;
    QListWidget *customerList;
    QListWidget *paragraphsList;

    QMenu *viewMenu;
};
//! [0]

#endif
