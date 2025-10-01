#ifndef __K_VALUE_BOX_H__
#define __K_VALUE_BOX_H__

#include <QLineEdit>

#include "kparambox.h"

// -------------------------------------------------------
// kvaluebox.h
// �����ߣ� �ӻ���
// ����ʱ�䣺 2025/4/26
// ���������� ��������е���ֵ������
// Copyright 2025 Kingsoft
// --------------------------------------------------------

class KValueBox : public KParamBox
{
	Q_OBJECT

	friend class MainWindow;
public:
	KValueBox(const QString &title,const qreal value,QWidget *parent);
	~KValueBox();
	virtual void focusInEvent(QFocusEvent* event) override;
private:
	QLineEdit *m_pParamEdit;
};

#endif
