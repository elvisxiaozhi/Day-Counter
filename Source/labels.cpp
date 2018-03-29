#include "labels.h"
#include <QDebug>
#include <QMouseEvent>
#include <QHoverEvent>

Labels::Labels()
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setAlignment(Qt::AlignCenter);
    setStyleSheet("QLabel { background-color: #FAD7A0; color: #8E44AD; font-size: 30px; }");

    setMouseTracking(true);
    setAttribute(Qt::WA_Hover);
}

void Labels::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        qDebug() << "Left Clicked";
        emit leftClicked();
    }
    if(event->button() == Qt::RightButton) {
        qDebug() << "Right Clicked";
    }
}

bool Labels::event(QEvent *event)
{
    switch(event->type())
    {
    case QEvent::HoverEnter:
        hoverEnter(static_cast<QHoverEvent*>(event));
        return true;
        break;
    case QEvent::HoverLeave:
        hoverLeave(static_cast<QHoverEvent*>(event));
        return true;
        break;
    default:
        break;
    }
    return QWidget::event(event);
}

void Labels::hoverEnter(QHoverEvent *event)
{
    qDebug() << event->type();
    emit hoverEntered();
}

void Labels::hoverLeave(QHoverEvent *event)
{
    qDebug() << event->type();
    emit hoverLeft();
}
