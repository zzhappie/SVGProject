#ifndef __K_PARAMS_BAR_H__
#define __K_PARAMS_BAR_H__

#include <QWidget>
#include <QLabel>
#include <QGridlayout>
#include <QVBoxLayout>

// -------------------------------------------------------
// kparambar.h
// �����ߣ� �ӻ���
// ����ʱ�䣺 2025/4/29
// ���������� ��������еĲ���������
// Copyright 2025 Kingsoft
// --------------------------------------------------------

class KParamsBar : public QWidget
{
	Q_OBJECT

public:
	KParamsBar(const QString &title,QWidget *parent);
	~KParamsBar();
protected:
	QGridLayout* m_pGridLayout;

private:
	QVBoxLayout* m_pVBoxLayout;
	QString m_title;
	QLabel* m_pTitleLabel;
};
#endif
