#ifndef __K_PARAM_BOX_H__
#define __K_PARAM_BOX_H__

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

#include "kglobaldata.h"

// -------------------------------------------------------
// kparambox.h
// 创建者： 钟欢欢
// 创建时间： 2025/4/26
// 功能描述： 属性面板中的参数框基类
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