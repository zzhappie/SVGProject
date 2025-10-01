#ifndef __K_CANVAS_PARAMS_BAR_H__
#define __K_CANVAS_PARAMS_BAR_H__

#include "kparamsbar.h"
#include "kcolorbox.h"
#include "kvaluebox.h"

// -------------------------------------------------------
// kcanvasparamsbar.h
// �����ߣ� �ӻ���
// ����ʱ�䣺 2025/4/30
// ���������� ��������еĻ����������
// Copyright 2025 Kingsoft
// --------------------------------------------------------

class KCanvasParamsBar : public KParamsBar
{
	Q_OBJECT
	friend class MainWindow;
public:
	KCanvasParamsBar(const QString &title,QWidget *parent);
	~KCanvasParamsBar();
private:
	KValueBox *m_pWidthBox;
	KValueBox *m_pHeightBox;
	KValueBox* m_pScaleBox;
	KColorBox* m_pColorBox;
};
#endif
