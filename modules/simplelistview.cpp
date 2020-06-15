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

#include "simplelistview.h"
#include "simplelistmodel.h"
#include <QApplication>
#include <QMouseEvent>
#include <QScrollBar>
#include <QModelIndex>
#include <QDebug>

SimpleListView::SimpleListView(QWidget *parent)
    : QListView(parent)
{
    setVerticalScrollMode(ScrollPerPixel);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setEditTriggers(QAbstractItemView::SelectedClicked | QAbstractItemView::DoubleClicked);
    setFocusPolicy(Qt::NoFocus);
    setAutoScroll(false);
    setFixedHeight(105);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode ( QAbstractItemView::SingleSelection);

    connect(this,&QListView::clicked,this,&SimpleListView::selectHistory);
    connect(verticalScrollBar(), &QScrollBar::rangeChanged, this, &SimpleListView::adjustScrollbarMargins);
    //connect(model(), &QAbstractListModel::updateCount, this, &QListView::updateCount);
}

SimpleListView::~SimpleListView()
{
}

void SimpleListView::mouseMoveEvent(QMouseEvent *e)
{
    if (e->x() < width() - 12) {
        QWidget::mouseMoveEvent(e);
    } else {
        QListView::mouseMoveEvent(e);
    }
}

void SimpleListView::selectHistory(const QModelIndex &index)
{
    int row = index.row();
}

void SimpleListView::adjustScrollbarMargins()
{
    if (!isVisible()) {
        return;
    }

    QEvent event(QEvent::LayoutRequest);
    QApplication::sendEvent(this, &event);

    if (!verticalScrollBar()->visibleRegion().isEmpty()) {
        setViewportMargins(0, 0, -verticalScrollBar()->sizeHint().width(), 0);
    } else {
        setViewportMargins(0, 0, 0, 0);
    }
}

void SimpleListView::mousePressEvent(QMouseEvent *event)
{
    static_cast<SimpleListModel *>(model())->refrushModel();
}
