#ifndef ADDDATEWINDOW_H
#define ADDDATEWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QPushButton>
#include <QCalendarWidget>

extern QVector<QString> dateNamesVec;
extern QVector<QString> datesVec;

class AddDateWindow : public QDialog
{
    Q_OBJECT
public:
    explicit AddDateWindow(QDialog *parent = nullptr);

private:
    QVBoxLayout *mainVLayout;
    QHBoxLayout *dateNameHLayout, *dateHLayout, *buttonHLayout;
    QLabel *dateNameLabel, *dateLabel;
    QLineEdit *dateNameEdit;
    QDateEdit *dateEdit;
    QPushButton *threeDotsBtn, *doneButton;
    QCalendarWidget *calendarWidget;
    bool calendarShowed;
    void setLayout();

signals:
    void newDateCreated();

private slots:
    void threeDotsBtnClicked();
    void writeXmlFile();
    void readXmlFile();
};

#endif // ADDDATEWINDOW_H
