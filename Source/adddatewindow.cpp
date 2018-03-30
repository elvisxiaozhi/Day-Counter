#include "adddatewindow.h"
#include "mainwindow.h"
#include <QDebug>

AddDateWindow::AddDateWindow(QDialog *parent) : QDialog(parent)
{
    setWindowTitle("Set A Date");
    setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    setLayout();
}

void AddDateWindow::setLayout()
{
    mainVLayout = new QVBoxLayout(this);

    dateNameHLayout = new QHBoxLayout;
    mainVLayout->addLayout(dateNameHLayout);

    dateNameLabel = new QLabel;
    dateNameHLayout->addWidget(dateNameLabel);
    dateNameLabel->setText("Name:");
    dateNameLabel->setStyleSheet("QLabel { background-color: #909497; color: #145A32; font-size: 20px; }");

    dateNameEdit = new QLineEdit;
    dateNameHLayout->addWidget(dateNameEdit);

    dateHLayout = new QHBoxLayout;
    mainVLayout->addLayout(dateHLayout);

    dateLabel = new QLabel;
    dateHLayout->addWidget(dateLabel);
    dateLabel->setText("Start Date:");
    dateLabel->setStyleSheet("QLabel { background-color: #909497; color: #145A32; font-size: 20px; }");

    dateEdit = new QDateEdit;
    dateHLayout->addWidget(dateEdit);
    dateEdit->setDate(QDate::currentDate());

    threeDotsBtn = new QPushButton;
    dateHLayout->addWidget(threeDotsBtn);
    threeDotsBtn->setText("…");
    threeDotsBtn->setMaximumWidth(30);
    connect(threeDotsBtn, &QPushButton::clicked, this, &AddDateWindow::threeDotsBtnClicked);

    calendarWidget = new QCalendarWidget;
    mainVLayout->addWidget(calendarWidget);
    calendarWidget->hide();
    calendarShowed = false;
    calendarWidget->setGridVisible(true);
    connect(calendarWidget, &QCalendarWidget::selectionChanged, [this](){ dateEdit->setDate(calendarWidget->selectedDate()); });

    buttonHLayout = new QHBoxLayout;
    mainVLayout->addLayout(buttonHLayout);

    QSpacerItem *btnSpacer = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Fixed);
    buttonHLayout->addSpacerItem(btnSpacer);

    doneButton = new QPushButton;
    buttonHLayout->addWidget(doneButton);
    doneButton->setText("Done");
    connect(doneButton, &QPushButton::clicked, this, &AddDateWindow::writeXmlFile);
}

void AddDateWindow::threeDotsBtnClicked()
{
    if(calendarShowed == true) {
        calendarWidget->hide();
        calendarShowed = false;
    }
    else {
        calendarWidget->show();
        calendarShowed = true;
    }
}

void AddDateWindow::writeXmlFile()
{
    MainWindow::isDataFileEmpty();
}
