#include "adddatewindow.h"
#include "mainwindow.h"
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>

QVector<QString> dateNamesVec;
QVector<QString> datesVec;

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
    connect(doneButton, &QPushButton::clicked, [this](){
        dateNamesVec.push_back(dateNameEdit->text());
        datesVec.push_back(dateEdit->date().toString("yyyy.MM.dd"));
        writeXmlFile();
    });
    connect(doneButton, &QPushButton::clicked, [this](){ this->close(); emit newDateCreated(); });
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
    if(file.open(QIODevice::WriteOnly)) {
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("dates");
        for(int i = 0; i < dateNamesVec.size(); i++) {
            xmlWriter.writeStartElement("date");
            if(dateNamesVec[i] == "") {
                xmlWriter.writeTextElement("name", "Null");
            }
            else {
                xmlWriter.writeTextElement("name", dateNamesVec[i]);
            }
            xmlWriter.writeTextElement("start-date", datesVec[i]);
            xmlWriter.writeEndElement();
        }
        xmlWriter.writeEndDocument();
        file.close();
    }
}

void AddDateWindow::readXmlFile()
{
    QXmlStreamReader xmlReader;
    QFile file(userDataPath);
    file.open(QIODevice::ReadOnly);
    xmlReader.setDevice(&file);
    while(!xmlReader.atEnd()) {
        QXmlStreamReader::TokenType token = xmlReader.readNext();
        if(token == QXmlStreamReader::StartElement) {
            if(xmlReader.name() == "date") {
                continue;
            }
            if(xmlReader.name() == "name") {
                dateNamesVec.push_back(xmlReader.readElementText());
            }
            if(xmlReader.name() == "start-date") {
                datesVec.push_back(xmlReader.readElementText());
            }
        }
    }
    file.close();
}
