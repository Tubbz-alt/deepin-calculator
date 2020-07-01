#ifndef MEMORYWIDGET_H
#define MEMORYWIDGET_H
/*******************************************************************************
 1. @类名:    MemoryWidget
 2. @作者:    京洲
 3. @日期:    2020-07-01
 4. @说明:    简易模式内存界面
*******************************************************************************/
#include <QWidget>
#include <DPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QList>
#include <QObject>
#include "memoryitemwidget.h"
#include "memorylistwidget.h"
#include "../core/evaluator.h"
#include "../widgets/iconbutton.h"
#include "memoryitemdelegate.h"

class MemoryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MemoryWidget(int mode = 0, QWidget *parent = nullptr);
    ~MemoryWidget();

    void generateData(Quantity answer);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
//    bool event(QEvent *event);

    void memoryplus(Quantity answer);
    void memoryminus(Quantity answer);
    void memoryclean();//内存列表为空时插入一个item
    QPair<QString, Quantity> getfirstnumber();//MR

    void widgetplusslot(int row, Quantity answer);
    void widgetminusslot(int row, Quantity answer);

signals:
    void widgetplus(int row);
    void widgetminus(int row);
    void insidewidget();
    void mListUnavailable();
    void mListAvailable();
    void itemclick(const QPair<QString, Quantity>);
    void themechange(int type);
    void widgetclean(int row, int mode);
    void memorycleansignal();
private:
    MemoryListWidget *m_listwidget;
    QPoint m_mousepoint;
    IconButton *m_clearbutton;
    int m_type;
    bool m_isempty;
    Evaluator *m_evaluator;
    Quantity m_ans;
    bool m_ansVaild;
    QList<Quantity> m_list; //ans的list
    int m_themetype = 0;
    int m_calculatormode;//0-标准下拉 1-科学右侧
    int m_line = 1; //item数字行数
    MemoryItemDelegate *m_memoryDelegate;
    int m_itemwidth = 0;
    int m_precision = -1;//计算精度

private:
    QString formatExpression(const QString &text);
    QString setitemwordwrap(const QString &text, int row = 0);
//    void nothinginmemory(); //内存列表为空时插入一个item
    void emptymemoryfontcolor();
public slots:
//    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void setThemeType(int type);
    void expressionempty(bool b);
    void widgetcleanslot(int row, int mode);
};


#endif // MEMORYWIDGET_H
