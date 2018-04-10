#ifndef LABELS_H
#define LABELS_H

#include <QLabel>
#include <QMenu>

class Labels : public QLabel
{
    Q_OBJECT
public:
    Labels();

private:
    QMenu *labelMenu;
    QAction *upAction, *downAction, *detailAction, *deleteAction;
    void mousePressEvent(QMouseEvent *);
    bool event(QEvent *event);
    void hoverEnter(QHoverEvent *event);
    void hoverLeave(QHoverEvent *event);
    void setMenu();

signals:
    void hoverEntered();
    void hoverLeft();
    void leftClicked();
    void deleteActionTriggered();

private slots:
};

#endif // LABELS_H
