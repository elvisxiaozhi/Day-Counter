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
//    if(checkFileExistence() == false) {
//        noDateLabel->setTextFormat(Qt::RichText);
//        noDateLabel->setText("<img src = :/add_button.png align = right width = '40' height = '40'> No Data added");
//    }
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

    labelsHLayout = new QHBoxLayout;
    mainVLayout->addLayout(labelsHLayout);
    labelsHLayout->setSpacing(0);

    noDateLabel = new Labels();
    noDateLabel->setText("No Date Added");
    noDateLabel->setMinimumSize(250, 100);
    labelsHLayout->addWidget(noDateLabel);

    addButtonLabel = new Labels();
    labelsHLayout->addWidget(addButtonLabel);
    addButtonLabel->setPixmap(QPixmap(":/add_button.png"));
    addButtonLabel->setAttribute(Qt::WA_Hover);
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
