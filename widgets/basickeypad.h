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

#ifndef BASICKEYPAD_H
#define BASICKEYPAD_H

#include <QWidget>
#include <QGridLayout>
#include <QSignalMapper>
#include <DGuiApplicationHelper>
#include <DSuggestButton>
#include "textbutton.h"
#include "iconbutton.h"
#include "equalbutton.h"

DWIDGET_USE_NAMESPACE
DGUI_USE_NAMESPACE

class BasicKeypad : public DWidget
{
    Q_OBJECT

public:
    enum Buttons {
        Key_Clear, Key_Percent, Key_Backspace, Key_Div,
        Key_7, Key_8, Key_9, Key_Mult,
        Key_4, Key_5, Key_6, Key_Min,
        Key_1, Key_2, Key_3, Key_Plus,
        Key_0, Key_Point, Key_Brackets, Key_Equals
    };

    BasicKeypad(QWidget *parent = nullptr);
    ~BasicKeypad();

    QPushButton *button(Buttons key);
    DSuggestButton *button();
    void animate(Buttons key);
    void animate();

    static const struct KeyDescription {
        QString text;
        Buttons button;
        int row;
        int column;
    } keyDescriptions[];
public slots:
    void initButtons();
    void buttonThemeChanged(int type);
signals:
    void buttonPressed(int);
    void equalPressed();
    void moveLeft();
    void moveRight();

private:
    void initUI();

private:
    QGridLayout *m_layout;
    QSignalMapper *m_mapper;
    QHash<Buttons, QPair<QPushButton *, const KeyDescription *>> m_keys;
    //DSuggestButton *m_equal;
    //EqualButton *m_equal;
};

#endif
