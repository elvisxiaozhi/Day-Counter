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
    QVBoxLayout *mainVLayout, *lblVLayout;
    QHBoxLayout *labelsHLayout;
    Labels *noDateLabel;
    Labels *addButtonLabel;
    AddDateWindow setDate;
    QVector<Labels *> dateLabels;
    void setLayout();
    void makeDataFile();
    int countDays(QString);

private slots:
    void hoverEntered();
    void hoverLeft();
    void leftClicked();
    void showNewDate();
};

#endif // MAINWINDOW_H
