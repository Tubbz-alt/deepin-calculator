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

#include "mainwindow.h"
#include "dtitlebar.h"
#include "dthememanager.h"
#include "dhidpihelper.h"
#include "utils.h"

#include <DWidgetUtil>
#include <DPalette>

#include <QPainter>
#include <QLabel>
#include <QDebug>
#include <QShortcut>
#include <QProcess>

DGUI_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent),
      m_settings(DSettings::instance()),
      m_tbMenu(new DMenu)
{
    //titlebar()->setBackgroundTransparent(true);
    QIcon t_icon = QIcon::fromTheme("deepin-calculator");
//    QPixmap pixmap = t_icon.pixmap(24,24);
//    QIcon newIcon(pixmap);
    titlebar()->setIcon(t_icon);
    titlebar()->setMenu(m_tbMenu);
    titlebar()->setTitle("");

    // init titlebar menu.
    //m_themeAction = new QAction(tr("Dark theme"), this);
    //m_themeAction->setCheckable(true);
    m_simpleAction = new QAction(/*tr*/("Simple mode"), this);
    m_scAction = new QAction(/*tr*/("Scientific mode"), this);
    //m_tbMenu->addAction(m_themeAction);

#ifdef ENABLE_SCIENTIFIC
    m_tbMenu->addAction(m_simpleAction);
    m_tbMenu->addAction(m_scAction);
#endif

    //m_tbMenu->addSeparator();

    initModule();
    initTheme();

    setWindowTitle(tr("Calculator"));

    m_basicModule->setFocus();
    //connect(m_themeAction, &QAction::triggered, this, &MainWindow::switchTheme);
    connect(DGuiApplicationHelper::instance(), &DGuiApplicationHelper::themeTypeChanged, this, &MainWindow::initTheme);
    connect(m_simpleAction, &QAction::triggered, this, &MainWindow::switchToSimpleMode);
    connect(m_scAction, &QAction::triggered, this, &MainWindow::switchToScientificMode);

    //QShortcut *viewshortcut = new QShortcut(this);
    //viewshortcut->setKey(QKeySequence(QLatin1String("Ctrl+Shift+/")));
    //connect(viewshortcut, SIGNAL(activated()), this, SLOT(onViewShortcut()));
}

MainWindow::~MainWindow()
{
}

/*void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_titlebarColor);
    painter.drawRect(QRect(0, 0, rect().width(), titlebar()->height()));

    DMainWindow::paintEvent(e);
}*/

void MainWindow::initTheme()
{
    int type = DGuiApplicationHelper::instance()->paletteType();
    if (type == 0)
        type = DGuiApplicationHelper::instance()->themeType();
    if (type == 1) {
        DPalette titlePa = titlebar()->palette();
        titlePa.setColor(DPalette::Light, QColor(240, 240, 240));
        titlePa.setColor(DPalette::Dark, QColor(240, 240, 240));
        titlePa.setColor(DPalette::Base, QColor(240, 240, 240));
        titlebar()->setPalette(titlePa);
    } else {
        DPalette titlePa = titlebar()->palette();
        titlePa.setColor(DPalette::Light, QColor(37, 37, 37));
        titlePa.setColor(DPalette::Dark, QColor(37, 37, 37));
        titlePa.setColor(DPalette::Base, QColor(37, 37, 37));
        titlebar()->setPalette(titlePa);
    }
}

void MainWindow::initModule()
{
    int mode = m_settings->getOption("mode").toInt();
    QWidget *centralWidget = new QWidget(this);

    m_mainLayout = new QStackedLayout(centralWidget);
    centralWidget->setLayout(m_mainLayout);
    setCentralWidget(centralWidget);

    m_basicModule = new BasicModule(this);

    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->addWidget(m_basicModule);

    switch (mode) {
    case 0:
        switchToSimpleMode();
        break;
    case 1:
        switchToScientificMode();
        break;
    }
}

/*void MainWindow::switchTheme()
{
    const QString theme = DThemeManager::instance()->theme();

    if (theme == "light") {
        m_settings->setOption("theme", "dark");
    } else {
        m_settings->setOption("theme", "light");
    }

    initTheme();
}*/

void MainWindow::switchToSimpleMode()
{
    m_basicModule->switchToSimpleKeypad();
    m_mainLayout->setCurrentIndex(0);
    m_settings->setOption("mode", 0);
    setFixedSize(344, 510);
}

void MainWindow::switchToScientificMode()
{
    m_basicModule->switchToScientificKeypad();
    m_mainLayout->setCurrentIndex(0);
    m_settings->setOption("mode", 1);
    setFixedSize(565, 505);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    m_basicModule->setKeyPress(event);
    return;
}

/*void MainWindow::onViewShortcut()
{
    QRect rect = window()->geometry();
    QPoint pos(rect.x() + rect.width() / 2, rect.y() + rect.height() / 2);
    Shortcut sc;
    QStringList shortcutString;
    QString param1 = "-j=" + sc.toStr();
    QString param2 = "-p=" + QString::number(pos.x()) + "," + QString::number(pos.y());
    shortcutString << "-b" << param1 << param2;

    QProcess *shortcutViewProc = new QProcess(this);
    shortcutViewProc->startDetached("killall deepin-shortcut-viewer");
    shortcutViewProc->startDetached("deepin-shortcut-viewer", shortcutString);

    connect(shortcutViewProc, SIGNAL(finished(int)), shortcutViewProc, SLOT(deleteLater()));
}*/

