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
    setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this, &Labels::customContextMenuRequested, [this](){ labelMenu->exec(QCursor::pos()); });
    setMenu();
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

void Labels::setMenu()
{
    labelMenu = new QMenu(this);
    upAction = new QAction("Up", labelMenu);
    downAction = new QAction("Down", labelMenu);
    detailAction = new QAction("Detail", labelMenu);
    deleteAction = new QAction("Delete", labelMenu);
    labelMenu->addAction(upAction);
    labelMenu->addAction(downAction);
    labelMenu->addAction(detailAction);
    labelMenu->addAction(deleteAction);
    connect(deleteAction, &QAction::triggered, [this](){ emit deleteActionTriggered(); });
}
