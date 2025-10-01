#ifndef __K_VALUE_BOX_H__
#define __K_VALUE_BOX_H__

#include <QLineEdit>

#include "kparambox.h"

// -------------------------------------------------------
// kvaluebox.h
// 创建者： 钟欢欢
// 创建时间： 2025/4/26
// 功能描述： 属性面板中的数值参数框
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
