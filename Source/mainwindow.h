#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "labels.h"
#include "adddatewindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QWidget *mainWidget;
    QVBoxLayout *mainVLayout;
    QHBoxLayout *labelsHLayout;
    QString dataPath;
    Labels *noDateLabel;
    Labels *addButtonLabel;
    AddDateWindow setDate;
    void setLayout();
    void makeDataFolder();
    bool checkFileExistence();

private slots:
    void hoverEntered();
    void hoverLeft();
    void leftClicked();
};

#endif // MAINWINDOW_H
