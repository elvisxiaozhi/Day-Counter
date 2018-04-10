#include "mainwindow.h"
#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <QFileInfo>

QString dataPath = "";
QString userDataPath = "";
const QString MainWindow::colorBase[MAX_NUMS] = {
    "#FADBD8", "#EBDEF0", "#D4E6F1", "#FDEBD0", "#AEB6BF"
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setLayout();
    makeDataFile();
    setDate.readXmlFile();
    if(isDataFileEmpty() == false) {
        showNewDate();
    }

    connect(&setDate, &AddDateWindow::newDateCreated, [this](){ delete lblVLayout; });
    connect(&setDate, &AddDateWindow::newDateCreated, this, &MainWindow::showNewDate);
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
    connect(addButtonLabel, &Labels::hoverEntered, this, &MainWindow::hoverEntered);
    connect(addButtonLabel, &Labels::hoverLeft, this, &MainWindow::hoverLeft);
    connect(addButtonLabel, &Labels::leftClicked, this, &MainWindow::leftClicked);
}

void MainWindow::makeDataFile()
{
    QStringList homePath = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
    dataPath = homePath.first() + "/AppData/Local/Day-Counter";
    if(!QDir().exists(dataPath)) {
        QDir().mkdir(dataPath);
    }
    userDataPath = dataPath + "/userData.xml";
    QFile file(userDataPath);
    if(file.open(QIODevice::ReadWrite)) {
        qDebug() << "Data file created";
    }
    file.close();
}

int MainWindow::countDays(QString dateString)
{
    QDate currentDate(QDate::currentDate());
    dateString.replace(".", "/");
    QDate endDate = QDate::fromString(dateString, "yyyy/MM/dd");
    return currentDate.daysTo(endDate);
}

int MainWindow::getLabelInfo()
{
    QLabel *labelSender = qobject_cast<QLabel *>(sender());
    return labelSender->objectName().toInt();
}

bool MainWindow::isDataFileEmpty()
{
    int lines = 0;
    QFile file(userDataPath);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream read(&file);
        while(!read.atEnd()) {
            read.readLine();
            lines++;
        }
    }
    file.close();
    if(lines == 0 || lines == 1) {
        qDebug() << "File is empty";
        return true;
    }
    qDebug() << "File lines: " << lines;
    return false;
}

void MainWindow::hoverEntered()
{
    addButtonLabel->setStyleSheet("QLabel { background-color: #3498DB; color: #8E44AD; font-size: 30px; }");
}

void MainWindow::hoverLeft()
{
    addButtonLabel->setStyleSheet("QLabel { background-color: #FAD7A0; color: #8E44AD; font-size: 30px; }");
}

void MainWindow::leftClicked()
{
    setDate.show();
}

void MainWindow::showNewDate()
{
    noDateLabel->hide();

    lblVLayout = new QVBoxLayout;
    mainVLayout->addLayout(lblVLayout);

    dateLabels.clear();
    dateLabels.resize(dateNamesVec.size());
    for(int i = 0; i < dateNamesVec.size(); i++) {
        dateLabels[i] = new Labels();
        dateLabels[i]->setObjectName(QString::number(i));
        dateLabels[i]->setWordWrap(true);

        int colorChoice = rand() % MAX_NUMS;
        dateLabels[i]->setStyleSheet(QString("QLabel { background-color: %1; color: #8E44AD; font-size: 30px; }").arg(colorBase[colorChoice]));

        if(countDays(datesVec[i]) < 0) {
            dateLabels[i]->setText(QString::number(abs(countDays(datesVec[i]))) + " days\nsince \n" + dateNamesVec[i]); //abs(...) is used for showing absolute value
        }
        else {
           dateLabels[i]->setText(QString::number(countDays(datesVec[i])) + " days\nuntil \n" + dateNamesVec[i]);
        }
        lblVLayout->addWidget(dateLabels[i]);

        connect(dateLabels[i], &Labels::deleteActionTriggered, this, &MainWindow::deleteDate);
    }

    mainVLayout->addWidget(addButtonLabel);
}

void MainWindow::deleteDate()
{
    dateNamesVec.erase(dateNamesVec.begin() + getLabelInfo());
    datesVec.erase(datesVec.begin() + getLabelInfo());
    for(int i = 0; i < dateLabels.size(); i++) { //note the dateLabel.size()
        dateLabels[i]->deleteLater();
    }
    showNewDate();
    AddDateWindow::writeXmlFile();
}
