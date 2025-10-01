#ifndef __K_TOOL_BUTTON_H__
#define __K_TOOL_BUTTON_H__

#include <QRadioButton>
#include <QtSvg/QSvgRenderer>
#include <QPainter>

#include "kglobaldata.h"

// -------------------------------------------------------
// ktoolbutton.h
// �����ߣ� �ӻ���
// ����ʱ�䣺 2025/4/12
// ���������� ��߹������İ�ť
// Copyright 2025 Kingsoft
// --------------------------------------------------------

class KToolButton : public QRadioButton
{
	Q_OBJECT

public:
	KToolButton(KButtonFlag buttonflag, QWidget* parent);
	~KToolButton();

	void initToolButton();

	virtual void paintEvent(QPaintEvent* event) override;// ��ͼ�¼�
	virtual void enterEvent(QEvent* event) override; // �����������
	virtual void leaveEvent(QEvent* event) override; // �뿪�������
	virtual void mouseReleaseEvent(QMouseEvent* e) override;// ����ͷ��¼�

private slots:
	void onToggledButton(bool checked);

private:
	QString m_iconName;   //svg ͼ������
	QSvgRenderer* m_pSvgRenderer;    //���� svg ͼ��/ͼƬ�Ķ���ָ��
	KButtonFlag m_buttonFlag;    //��¼��ͼ����
};
#endif

