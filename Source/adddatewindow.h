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
    void readXmlFile();
    static void writeXmlFile();
    void editDate(int);

private:
    QVBoxLayout *mainVLayout;
    QHBoxLayout *dateNameHLayout, *dateHLayout, *buttonHLayout;
    QLabel *dateNameLabel, *dateLabel;
    QLineEdit *dateNameEdit;
    QDateEdit *dateEdit;
    QPushButton *threeDotsBtn, *doneButton, *doneEditButton;
    QCalendarWidget *calendarWidget;
    bool calendarShowed;
    void setLayout();
    void closeEvent(QCloseEvent *);

signals:
    void newDateCreated();
    void dateHasEdit(int);
    void editWindowClosed();

private slots:
    void threeDotsBtnClicked();
};

#endif // ADDDATEWINDOW_H
