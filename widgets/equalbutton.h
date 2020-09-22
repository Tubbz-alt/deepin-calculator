/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     rekols <rekols@foxmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef EQUALBUTTON_H
#define EQUALBUTTON_H

#include <DPushButton>
#include <DPalette>

#include <QGraphicsDropShadowEffect>

DWIDGET_USE_NAMESPACE
DGUI_USE_NAMESPACE

class EqualButton : public QPushButton
{
    Q_OBJECT
public:
    EqualButton(const QString &text = QString(), QWidget *parent = nullptr);
    ~EqualButton();

    void init();
    //void showShadow();
    //void hideShadow();
    void animate(int msec = 100);
signals:
    void moveLeft();
    void moveRight();
    void btnclicked();

public:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void paintEvent(QPaintEvent *e);
protected:
    void keyPressEvent(QKeyEvent *e);
private:
    QGraphicsDropShadowEffect *m_effect;

    DPalette m_palette;
    bool m_isHover;
    bool m_isPress;
    QFont m_font;
};

#endif // EQUALBUTTON_H
