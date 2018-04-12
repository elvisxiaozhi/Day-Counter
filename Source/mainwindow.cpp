#include "mainwindow.h"
#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <QFileInfo>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QCloseEvent>
#include <QSettings>
#include <QCoreApplication>

QString dataPath = "";
QString userDataPath = "";
const QString MainWindow::colorBase[MAX_NUMS] = {
    "#FADBD8", "#EBDEF0", "#D4E6F1", "#FDEBD0", "#AEB6BF"
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setLayout();
    setTrayIcon();
    makeDataFile();
    setDate.readXmlFile();
    if(isDataFileEmpty() == false) {
        showNewDate();
    }

    connect(&setDate, &AddDateWindow::newDateCreated, [this](){ delete lblVLayout; });
    connect(&setDate, &AddDateWindow::newDateCreated, this, &MainWindow::showNewDate);
    connect(&setDate, &AddDateWindow::dateHasEdit, this, &MainWindow::removeOldDate);
    connect(&setTimer, &Timer::newDayHasCome, this, &MainWindow::updateDays);

    statusBar()->showMessage(QString::number(dateLabels.size()) + " items");
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

void MainWindow::setTrayIcon()
{
    trayIcon = new QSystemTrayIcon(QIcon(":/add_button.png"), this);
    trayIcon->show();

    QMenu *trayIconMenu = new QMenu;
    trayIcon->setContextMenu(trayIconMenu);

    startOnBootAction = new QAction("Start on Boot", trayIcon);
    trayIconMenu->addAction(startOnBootAction);
    startOnBootAction->setCheckable(true);
    QAction *settingsAction = new QAction("Settings", trayIconMenu);
    trayIconMenu->addAction(settingsAction);

    QMenu *helpMenu = new QMenu("Help");
    trayIconMenu->addMenu(helpMenu);
    QAction *feedbackAction = new QAction("Feedback", helpMenu);
    helpMenu->addAction(feedbackAction);
    QAction *aboutAction = new QAction("About", helpMenu);
    helpMenu->addAction(aboutAction);
    QAction *donateAction = new QAction("Donate", helpMenu);
    helpMenu->addAction(donateAction);

    QAction *quitAction = new QAction("Quit", trayIconMenu);
    trayIconMenu->addAction(quitAction);

    connect(trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::trayIconActivated);
    connect(startOnBootAction, &QAction::changed, this, &MainWindow::startOnBootActionChanged);
    connect(settingsAction, &QAction::triggered, this, &MainWindow::showSettings);
    connect(quitAction, &QAction::triggered, [this](){ trayIcon->setVisible(false); this->close(); }); //note the program can be only closed by clicking "Quit" action
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
        file.close();
    }
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

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(trayIcon->isVisible()) { //if tray icon can be seen in the task bar
        event->ignore(); //then do not quit the program
        this->hide(); //instead of closing the program, just hide the main window
    }
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
        dateLabels[i]->setMinimumWidth(280); //set minimum width to let the window title completely show up
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

        connect(dateLabels[i], &Labels::upActionTriggered, this, &MainWindow::dateMoveUp);
        connect(dateLabels[i], &Labels::downActionTriggered, this, &MainWindow::dateMoveDown);
        connect(dateLabels[i], &Labels::editActionTriggered, this, &MainWindow::editDate);
        connect(dateLabels[i], &Labels::deleteActionTriggered, this, &MainWindow::deleteDate);
    }

    mainVLayout->addWidget(addButtonLabel);

    statusBar()->showMessage(QString::number(datesVec.size()) + " items");
}

void MainWindow::dateMoveUp()
{
    if(getLabelInfo() != 0) {
        std::iter_swap(dateNamesVec.begin() + getLabelInfo(), dateNamesVec.begin() + getLabelInfo() - 1);
        std::iter_swap(datesVec.begin() + getLabelInfo(), datesVec.begin() + getLabelInfo() - 1);
        for(int i = 0; i < dateLabels.size(); i++) { //note the dateLabel.size()
            dateLabels[i]->deleteLater();
        }
        AddDateWindow::writeXmlFile();
        showNewDate();
    }
}

void MainWindow::dateMoveDown()
{
    if(getLabelInfo() != dateLabels.size() - 1) {
        std::iter_swap(dateNamesVec.begin() + getLabelInfo(), dateNamesVec.begin() + getLabelInfo() + 1);
        std::iter_swap(datesVec.begin() + getLabelInfo(), datesVec.begin() + getLabelInfo() + 1);
        for(int i = 0; i < dateLabels.size(); i++) { //note the dateLabel.size()
            dateLabels[i]->deleteLater();
        }
        AddDateWindow::writeXmlFile();
        showNewDate();
    }
}

void MainWindow::editDate()
{
    setDate.show();
    setDate.editDate(getLabelInfo());
}

void MainWindow::removeOldDate()
{
    for(int i = 0; i < dateLabels.size(); i++) { //note the dateLabel.size()
        dateLabels[i]->deleteLater();
    }
    AddDateWindow::writeXmlFile();
    showNewDate();
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

void MainWindow::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == 2 || reason == 3) { //tray icon was double clicked or clicked
        this->showNormal(); //to show a normal size of the main window
    }
}

void MainWindow::startOnBootActionChanged()
{
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    if(startOnBootAction->isChecked()) {
        settings.setValue("Day-Counter", QCoreApplication::applicationFilePath().replace('/', '\\'));
    }
    else {
        settings.remove("Day-Counter");
    }
}

void MainWindow::showSettings()
{
    qDebug() << "Settings";
}

void MainWindow::showAboutPage()
{

}

void MainWindow::updateDays()
{
    for(int i = 0; i < dateNamesVec.size(); i++) {
        if(countDays(datesVec[i]) < 0) {
            dateLabels[i]->setText(QString::number(abs(countDays(datesVec[i]))) + " days\nsince \n" + dateNamesVec[i]); //abs(...) is used for showing absolute value
        }
        else {
           dateLabels[i]->setText(QString::number(countDays(datesVec[i])) + " days\nuntil \n" + dateNamesVec[i]);
        }
    }
}
