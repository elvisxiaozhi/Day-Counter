#include "mainwindow.h"
#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setLayout();
    makeDataFolder();
    if(checkFileExistence() == false) {
        noDateLabel->setText("No Date Added");
    }
}

MainWindow::~MainWindow()
{

}

void MainWindow::setLayout()
{
    setWindowTitle("Day-Counter");
    mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    mainVLayout = new QVBoxLayout;
    mainWidget->setLayout(mainVLayout);

    noDateLabel = new Labels();
    mainVLayout->addWidget(noDateLabel);
}

void MainWindow::makeDataFolder()
{
    QStringList homePath = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
    dataPath = homePath.first() + "/AppData/Local/Day-Counter";
    if(!QDir().exists(dataPath)) {
        QDir().mkdir(dataPath);
    }
}

bool MainWindow::checkFileExistence()
{
    QString userDataPath = dataPath + "/userData.xml";
    QFileInfo filePath(userDataPath);
    if(!filePath.exists()) {
        return false;
    }
    return true;
}
