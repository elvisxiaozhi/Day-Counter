#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include "labels.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QWidget *mainWidget;
    QVBoxLayout *mainVLayout;
    QString dataPath;
    Labels *noDateLabel;
    void setLayout();
    void makeDataFolder();
    bool checkFileExistence();
};

#endif // MAINWINDOW_H
