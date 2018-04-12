#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QDate>
#include <QTimer>

class Timer : public QObject
{
    Q_OBJECT
public:
    explicit Timer(QObject *parent = nullptr);

private:
    QStringList currentTimeStringList;
    QTimer *timer;

signals:
    void newDayHasCome();

public slots:

private slots:
    void updateTimer();
};

#endif // TIMER_H
