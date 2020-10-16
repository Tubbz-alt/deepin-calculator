#include "arrowrectangle.h"
#include <QDebug>
#include <DListWidget>
#include "views/memorylistwidget.h"

//static int init = 0;

ArrowRectangle::ArrowRectangle(ArrowDirection direction, FloatMode floatMode, QWidget *parent)
    : DArrowRectangle(direction, floatMode, parent)
{
    this->installEventFilter(this);
}

ArrowRectangle::~ArrowRectangle()
{

}

bool ArrowRectangle::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusOut) {
        //点击标题栏及外部桌面失去焦点时切换至scientifickeypad
        QFocusEvent *focus_Event = static_cast<QFocusEvent *>(event);
        if (focus_Event->reason() == Qt::MouseFocusReason || focus_Event->reason() == Qt::ActiveWindowFocusReason) {
            emit hidearrowrectangle();
        }
    }
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *key_event = static_cast < QKeyEvent *>(event); //将事件转化为键盘事件
        if (key_event->key() == Qt::Key_Escape) {
            emit hidearrowrectangle();
        } else if (key_event->key() == Qt::Key_Tab && getContent()) {
            if (obj == this) {
                static_cast<MemoryListWidget *>(getContent())->setFocus(Qt::TabFocusReason);
                return true;
            } else {
                this->setFocus(Qt::TabFocusReason);
                return true;
            }
        }
    }
//    if (obj == getContent()) {
//        if (event->type() == QEvent::KeyPress) {
//            QKeyEvent *key_event = static_cast < QKeyEvent *>(event); //将事件转化为键盘事件
//            if (key_event->key() == Qt::Key_Tab) {
//                qDebug() << "1";
//                getContent()->setFocus(Qt::TabFocusReason);
//                return true;
//            }
//        }
//    }
    return QWidget::eventFilter(obj, event);
}

void ArrowRectangle::focusInEvent(QFocusEvent *event)
{
//    if (init == 0 && getContent()) {
//        getContent()->installEventFilter(this);
//        init = 1;
//    }
    if (event->reason() == Qt::TabFocusReason) {
        static_cast<MemoryListWidget *>(getContent())->setFocus();
    }
    DArrowRectangle::focusInEvent(event);
}
