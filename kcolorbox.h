#ifndef __K_COLOR_BOX_H__
#define __K_COLOR_BOX_H__

#include <QPushButton>
#include <QColorDialog>

#include "kparambox.h"

// -------------------------------------------------------
// kcolorbox.h
// �����ߣ� �ӻ���
// ����ʱ�䣺 2025/4/27
// ���������� ��������е���ɫѡ���
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