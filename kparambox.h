#ifndef __K_PARAM_BOX_H__
#define __K_PARAM_BOX_H__

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

#include "kglobaldata.h"

// -------------------------------------------------------
// kparambox.h
// �����ߣ� �ӻ���
// ����ʱ�䣺 2025/4/26
// ���������� ��������еĲ��������
// Copyright 2025 Kingsoft
// --------------------------------------------------------

class KParamBox : public QWidget
{
	Q_OBJECT

public:
	KParamBox(const QString &title,QWidget *parent);
	~KParamBox();
	virtual void enterEvent(QEvent* event) override;
	virtual void leaveEvent(QEvent* event) override;
protected:
	QVBoxLayout* m_pVLayout;
private:
	QString m_title;
	QLabel* m_pTitleLabel;
};
#endif