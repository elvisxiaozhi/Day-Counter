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

private:
    QWidget *mainWidget;
    QVBoxLayout *mainVLayout, *lblVLayout;
    QHBoxLayout *labelsHLayout;
    Labels *noDateLabel;
    Labels *addButtonLabel;
    AddDateWindow setDate;
    QVector<Labels *> dateLabels;
    static const int MAX_NUMS = 5;
    static const QString colorBase[MAX_NUMS];
    void setLayout();
    void setMenuBar();
    static bool isDataFileEmpty();
    void makeDataFile();
    int countDays(QString);
    int getLabelInfo();

signals:

private slots:
    void hoverEntered();
    void hoverLeft();
    void leftClicked();
    void showNewDate();
    void dateMoveUp();
    void dateMoveDown();
    void editDate();
    void removeOldDate();
    void deleteDate();
    void showSettings();
    void showAboutPage();
};

#endif // MAINWINDOW_H
