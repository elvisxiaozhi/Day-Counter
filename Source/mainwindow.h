#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "labels.h"
#include "adddatewindow.h"

extern QString dataPath;
extern QString userDataPath;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static bool isDataFileEmpty();

private:
    QWidget *mainWidget;
    QVBoxLayout *mainVLayout;
    QHBoxLayout *labelsHLayout;
    Labels *noDateLabel;
    Labels *addButtonLabel;
    AddDateWindow setDate;
    void setLayout();
    void makeDataFolder();

private slots:
    void hoverEntered();
    void hoverLeft();
    void leftClicked();
};

#endif // MAINWINDOW_H
