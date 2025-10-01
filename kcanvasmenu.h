#ifndef __K_CANVAS_MENU_H__
#define __K_CANVAS_MENU_H__

// -------------------------------------------------------
// kcanvasmenu.h
// 创建者： 钟欢欢
// 创建时间： 2025/4/24
// 功能描述： 画布的右键菜单栏
// Copyright 2025 Kingsoft
// --------------------------------------------------------

#include <QObject>
#include <QMenu>
#include <QAction>
#include <QPoint>

class KCanvasMenu : public QObject
{
    Q_OBJECT

    friend class KSvgMainWindow;
    friend class MainWindow;
public:
    explicit KCanvasMenu(QWidget* parent = nullptr);
    ~KCanvasMenu();

    void showMenu(const QPoint& pos);

    bool getIsSelectedShape();
    void setIsSelectedShape(bool ok);

private:
    void initializeMenu();
    void updateActions();

    bool m_isSelectedShape;

    QWidget* m_parentWidget;
    QMenu* m_menu;

    QAction* m_selectAllAct; // 全选
    QAction* m_undoAct; // 撤销
    QAction* m_redoAct; // 重做
    QAction* m_cutAct; // 剪切
    QAction* m_copyAct; // 复制
    QAction* m_pasteAct; // 粘贴
    QAction* m_deleteAct; // 删除
    QAction* m_upLayerAct; // 置于上层
    QAction* m_downLayerAct; // 置于下层
    QAction* m_upTopLayerAct; // 置于顶层
    QAction* m_downBottomLayerAct; // 置于底层
};
#endif 


