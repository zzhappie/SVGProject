#ifndef __K_SHAPE_PARAMS_BAR_H__
#define __K_SHAPE_PARAMS_BAR_H__

#include "kparamsbar.h"
#include "kcolorbox.h"
#include "kvaluebox.h"
#include "kcombobox.h"
#include "kcanvasmenu.h"

// -------------------------------------------------------
// kshapeparamsbar.h
// 创建者： 钟欢欢
// 创建时间： 2025/4/29
// 功能描述： 属性面板中的图形参数面板
// Copyright 2025 Kingsoft
// --------------------------------------------------------

class KShapeParamsBar : public KParamsBar
{
	Q_OBJECT
		friend class MainWindow;
public:
	KShapeParamsBar(const QString& title, QWidget* parent);
	~KShapeParamsBar();

private:
	KValueBox* m_pBorderWidthBox;
	KComboBox* m_pBorderStyleBox;
	KColorBox* m_pBorderColorBox;
	KColorBox* m_pFillColorBox;
	KValueBox* m_pShapeWidthBox;
	KValueBox* m_pShapeHeightBox;
};
#endif