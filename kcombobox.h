#ifndef __K_COMBO_BOX_H__
#define __K_COMBO_BOX_H__

#include "kparambox.h"

#include <QComboBox>

// -------------------------------------------------------
// kcomb0box.h
// 创建者： 钟欢欢
// 创建时间： 2025/4/28
// 功能描述： 属性面板中的下拉选择框
// Copyright 2025 Kingsoft
// --------------------------------------------------------

class KComboBox : public KParamBox
{
	Q_OBJECT

	friend class MainWindow;
public:
	KComboBox(const QString& title, QWidget* parent);
	~KComboBox();

	void addItemWithIcon(const QIcon& icon);
	
private:
	QComboBox* m_pBorderStyleComboBox;
	void initItemCount(const int count);
};
#endif