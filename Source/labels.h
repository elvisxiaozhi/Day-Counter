#ifndef LABELS_H
#define LABELS_H

#include <QLabel>

class Labels : public QLabel
{
public:
    Labels();

private:
    void mousePressEvent(QMouseEvent *);
    bool hoverEvent(QHoverEvent *);
    void hoverEnter(QHoverEvent *);
};

#endif // LABELS_H
