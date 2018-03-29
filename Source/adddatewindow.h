#ifndef ADDDATEWINDOW_H
#define ADDDATEWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QPushButton>

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
    QPushButton *doneButton;
    void setLayout();

signals:

private slots:
    void writeXmlFile();
};

#endif // ADDDATEWINDOW_H
