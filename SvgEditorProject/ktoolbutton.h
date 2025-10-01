#ifndef __K_TOOL_BUTTON_H__
#define __K_TOOL_BUTTON_H__

#include <QRadioButton>
#include <QtSvg/QSvgRenderer>
#include <QPainter>

#include "kglobaldata.h"

// -------------------------------------------------------
// ktoolbutton.h
// 创建者： 钟欢欢
// 创建时间： 2025/4/12
// 功能描述： 侧边工具栏的按钮
// Copyright 2025 Kingsoft
// --------------------------------------------------------

class KToolButton : public QRadioButton
{
	Q_OBJECT

public:
	KToolButton(KButtonFlag buttonflag, QWidget* parent);
	~KToolButton();

	void initToolButton();

	virtual void paintEvent(QPaintEvent* event) override;// 绘图事件
	virtual void enterEvent(QEvent* event) override; // 进入组件区域
	virtual void leaveEvent(QEvent* event) override; // 离开组件区域
	virtual void mouseReleaseEvent(QMouseEvent* e) override;// 鼠标释放事件

private slots:
	void onToggledButton(bool checked);

private:
	QString m_iconName;   //svg 图标名称
	QSvgRenderer* m_pSvgRenderer;    //处理 svg 图标/图片的对象指针
	KButtonFlag m_buttonFlag;    //记录绘图类型
};
#endif

