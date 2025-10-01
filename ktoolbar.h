#ifndef __K_SVG_TOOL_BAR_H__
#define __K_SVG_TOOL_BAR_H__

#include <QtSvg/qsvgrenderer>
#include <QPainter>
#include <QButtonGroup>
#include <QStyleOption>
#include <QLayout>

#include "ktoolbutton.h"

// -------------------------------------------------------
// ktoolbar.h
// 创建者： 钟欢欢
// 创建时间： 2025/4/12
// 功能描述： 侧边工具栏
// Copyright 2025 Kingsoft
// --------------------------------------------------------

class KToolBar : public QWidget
{
	Q_OBJECT

public:
	explicit KToolBar(QWidget *parent);
	~KToolBar();
private:
	QVBoxLayout* m_pVLayout;
	QButtonGroup* m_pBtnGroup;
	KToolButton* m_pMouseBtn;
	KToolButton* m_pPenBtn;
	KToolButton* m_pLineBtn;
	KToolButton* m_pRectBtn;
	KToolButton* m_pCircleBtn;
	KToolButton* m_pPentBtn;
	KToolButton* m_pHexaBtn;
	KToolButton* m_pStarBtn;
	KToolButton* m_pTextBtn;
	KToolButton* m_pZoomBtn;
	KToolButton* m_pHeartBtn;
	KToolButton* m_pBubbleBtn;
};
#endif
