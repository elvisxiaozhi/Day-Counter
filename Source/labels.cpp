#include "labels.h"
#include <QDebug>
#include <QMouseEvent>

Labels::Labels()
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setAlignment(Qt::AlignCenter);
    setStyleSheet("QLabel { background-color: #FAD7A0; color: #8E44AD; font-size: 30px; min-width: 300px;}");
}

void Labels::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton) {
        qDebug() << "Right Clicked";
    }
}
