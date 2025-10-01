#ifndef __K_COLOR_BOX_H__
#define __K_COLOR_BOX_H__

#include <QPushButton>
#include <QColorDialog>

#include "kparambox.h"

// -------------------------------------------------------
// kcolorbox.h
// 创建者： 钟欢欢
// 创建时间： 2025/4/27
// 功能描述： 属性面板中的颜色选择框
// Copyright 2025 Kingsoft
// --------------------------------------------------------

class KColorBox : public KParamBox
{
	Q_OBJECT

	friend class MainWindow;
public:
	KColorBox(const QString &title,const QString &rgbColorStr, KColorFlag flag,
		QWidget *parent);
	~KColorBox();

signals:
	void pickedColor();
private slots:
	void showPickColorDlg();
private:
	QPushButton* m_pColorBtn;
	KColorFlag m_colorFlag;
};
#endif