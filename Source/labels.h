#ifndef LABELS_H
#define LABELS_H

#include <QLabel>

class Labels : public QLabel
{
public:
    Labels();

private:
    void mousePressEvent(QMouseEvent *);
};

#endif // LABELS_H
