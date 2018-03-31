#include "adddatewindow.h"
#include "mainwindow.h"
#include <QFile>
#include <QXmlStreamWriter>
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
    dateNameEdit->setPlaceholderText("Null");

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
    connect(doneButton, &QPushButton::clicked, [this](){ this->close(); });
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
    QFile file(userDataPath);
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    if(MainWindow::isDataFileEmpty() == true) {
        if(file.open(QIODevice::WriteOnly)) {
            xmlWriter.writeStartDocument();
            xmlWriter.writeStartElement("Date");
            if(dateNameEdit->text() == "") {
                xmlWriter.writeTextElement("Name", dateNameEdit->placeholderText());
            }
            else {
                xmlWriter.writeTextElement("Name", dateNameEdit->text());
            }
            xmlWriter.writeTextElement("Start Date", dateEdit->date().toString());
            xmlWriter.writeEndDocument();
        }
    }
    else {
        if(file.open(QIODevice::WriteOnly | QIODevice::Append)) {
            xmlWriter.writeStartElement("Date");
            if(dateNameEdit->text() == "") {
                xmlWriter.writeTextElement("Name", "Null");
            }
            else {
                xmlWriter.writeTextElement("Name", dateNameEdit->text());
            }
            xmlWriter.writeTextElement("Start Date", dateEdit->date().toString());
            xmlWriter.writeEndDocument();
        }
    }
    file.close();
}
