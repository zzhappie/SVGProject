#ifndef __K_FILE_MENU_BAR_H__
#define __K_FILE_MENU_BAR_H__

#include <QMenuBar>
#include <QMenu>
#include <QAction>

// -------------------------------------------------------
// kfilemenubar.h
// 创建者： 钟欢欢
// 创建时间： 2025/5/2
// 功能描述： 文件菜单栏
// Copyright 2025 Kingsoft
// --------------------------------------------------------

class KFileMenuBar : public QMenuBar
{
    Q_OBJECT

	friend class MainWindow;
public:
    KFileMenuBar(QWidget* parent = Q_NULLPTR);
    ~KFileMenuBar();

private:
    void initFileMenu();

    QMenu* m_fileMenu;

    QAction* m_creatFileAct;
    QAction* m_openSVGAct;
    QAction* m_saveAct;
    QAction* m_savePNGAct;
};
#endif