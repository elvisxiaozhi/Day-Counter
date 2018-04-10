#ifndef MESSAGEBOXES_H
#define MESSAGEBOXES_H

#include <QMessageBox>

class MessageBoxes : public QObject
{
    Q_OBJECT
public:
    MessageBoxes();
    void showDeleteMsBox();

signals:
    void deletionConfirmed();
};

#endif // MESSAGEBOXES_H
