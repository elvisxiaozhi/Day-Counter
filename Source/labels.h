#ifndef LABELS_H
#define LABELS_H

#include <QLabel>
#include <QMenu>
#include "messageboxes.h"

class Labels : public QLabel
{
    Q_OBJECT
public:
    Labels();

private:
    QMenu *labelMenu;
    QAction *upAction, *downAction, *detailAction, *editAction, *deleteAction;
    MessageBoxes setDeleteMsBox;
    void mousePressEvent(QMouseEvent *);
    bool event(QEvent *event); //it has to be bool type
    void setMenu();

signals:
    void hoverEntered();
    void hoverLeft();
    void leftClicked();
    void upActionTriggered();
    void downActionTriggered();
    void deleteActionTriggered();

private slots:
};

#endif // LABELS_H
