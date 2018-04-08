#include "labels.h"
#include <QDebug>
#include <QMouseEvent>
#include <QHoverEvent>
#include <QMenu>

Labels::Labels()
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setAlignment(Qt::AlignCenter);
    setStyleSheet("QLabel { background-color: #FAD7A0; color: #8E44AD; font-size: 30px; }");

    setMouseTracking(true);
    setAttribute(Qt::WA_Hover);

    setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this, &Labels::customContextMenuRequested, this, &Labels::showMenu);
}

void Labels::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        qDebug() << "Left Clicked";
        emit leftClicked();
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

void Labels::showMenu(const QPoint &pos)
{
    QMenu contextMenu(tr("Context menu"), this);
    QAction upAction("Up", this);
    QAction downAction("Down", this);
    QAction detailAction("Detail", this);
    QAction deleteAction("Delete", this);
//        connect(&action1, SIGNAL(triggered()), this, SLOT(removeDataPoint()));

    contextMenu.addAction(&upAction);
    contextMenu.addAction(&downAction);
    contextMenu.addAction(&detailAction);
    contextMenu.addAction(&deleteAction);
    contextMenu.exec(mapToGlobal(pos));
}
