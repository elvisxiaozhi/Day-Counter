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
    setMenu();
}

void Labels::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        emit leftClicked();
    }
}

bool Labels::event(QEvent *event)
{
    if(event->type() == QEvent::HoverEnter) {
        emit hoverEntered();
    }
    if(event->type() == QEvent::HoverLeave) {
        emit hoverLeft();
    }
    return QWidget::event(event);
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
    connect(this, &Labels::customContextMenuRequested, [this](){ labelMenu->exec(QCursor::pos()); });
    connect(deleteAction, &QAction::triggered, [this](){ emit deleteActionTriggered(); });
}
