#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSystemTrayIcon>
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
    QSystemTrayIcon *trayIcon;
    QAction *startOnBootAction;
    static const int MAX_NUMS = 5;
    static const QString colorBase[MAX_NUMS];
    void setLayout();
    void setTrayIcon();
    static bool isDataFileEmpty();
    void makeDataFile();
    int countDays(QString);
    int getLabelInfo();
    void closeEvent(QCloseEvent *); //avoid closing the program when the tray icon is visible

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
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void setStartOnBoot();
    void showSettings();
    void showAboutPage();
};

#endif // MAINWINDOW_H
