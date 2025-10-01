#ifndef __K_PARAMS_BAR_H__
#define __K_PARAMS_BAR_H__

#include <QWidget>
#include <QLabel>
#include <QGridlayout>
#include <QVBoxLayout>

// -------------------------------------------------------
// kparambar.h
// 创建者： 钟欢欢
// 创建时间： 2025/4/29
// 功能描述： 属性面板中的参数面板基类
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
