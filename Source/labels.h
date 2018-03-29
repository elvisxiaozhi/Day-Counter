#ifndef LABELS_H
#define LABELS_H

#include <QLabel>

class Labels : public QLabel
{
    Q_OBJECT
public:
    Labels();

private:
    void mousePressEvent(QMouseEvent *);
    bool event(QEvent *event);
    void hoverEnter(QHoverEvent *event);
    void hoverLeave(QHoverEvent *event);

signals:
    void hoverEntered();
    void hoverLeft();
    void leftClicked();
};

#endif // LABELS_H
