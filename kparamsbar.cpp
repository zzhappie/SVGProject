#include "kparamsbar.h"

KParamsBar::KParamsBar(const QString &title,QWidget *parent)
	: QWidget(parent)
	, m_pVBoxLayout(Q_NULLPTR)
	, m_pGridLayout(Q_NULLPTR)
	, m_pTitleLabel(Q_NULLPTR)
	, m_title(title)
{
	setMaximumWidth(270);
	setMinimumWidth(270);
	setFocusPolicy(Qt::ClickFocus);//单击获得焦点
	setStyleSheet("background-color:#3f3f3c");
	
	m_pVBoxLayout = new QVBoxLayout(this);
	m_pVBoxLayout->setContentsMargins(10, 0, 10, 0);
	m_pVBoxLayout->setAlignment(Qt::AlignTop);

	m_pTitleLabel = new QLabel(this);
	m_pTitleLabel->setMaximumHeight(40);// 设置最大高度
	m_pTitleLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter); // 设置对齐
	m_pTitleLabel->setStyleSheet("background-color:rgb(52,52,52); font-size:24px; color:#FFFFFF; font-family: Microsoft YaHei");
	m_pTitleLabel->setText(m_title);

	m_pGridLayout = new QGridLayout();
	m_pGridLayout->setSpacing(10);

	m_pVBoxLayout->addWidget(m_pTitleLabel);
	m_pVBoxLayout->addLayout(m_pGridLayout);
}

KParamsBar::~KParamsBar()
{
}
