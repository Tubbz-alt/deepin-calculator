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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QStackedLayout>
#include <QMenu>
#include <DMainWindow>

#include "widgets/basicmodule.h"
#include "widgets/scientificmodule.h"
#include "control/iconbutton.h"
#include "dsettings.h"
#include "performancemonitor.h"

#define ENABLE_SCIENTIFIC 1

DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void windowChanged(int width, int height, bool hishide); //hishide-历史记录栏是否隐藏
public slots:
    //void onViewShortcut();
protected:
    //void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *event);
    void moveEvent(QMoveEvent *event);
    void resizeEvent(QResizeEvent *event);
    void closeEvent(QCloseEvent *event);

private:
    void initTheme();
    void initModule();
    void switchToSimpleMode();
    void switchToScientificMode();
    void showHistoryWidget();
    void hideHistoryWidget(bool hissetting);

private:
    DSettingsAlt *m_settings;
    QStackedLayout *m_mainLayout;
    DMenu *m_tbMenu;
    DMenu *m_modeshowmenu;
    QAction *m_simpleAction;
    QAction *m_scAction;
    QAction *m_hisAction;
    QActionGroup *m_pActionGroup;

    BasicModule *m_basicModule;
    scientificModule *m_scientificModule;
//    QSize m_lastscisize = QSize(); //切换回标准时模式时科学模式的size
    bool m_isinit = true;//初始化
    int m_firstInitMode = 0;//初始化的界面，0-标准 1-科学
    bool m_isStandInit = false; //标准是否初始化
    bool m_isSciInit = false; //科学是否初始化
};

#endif
