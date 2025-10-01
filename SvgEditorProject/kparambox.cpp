#include "kparambox.h"

KParamBox::KParamBox(const QString &title,QWidget *parent)
	: QWidget(parent)
	, m_title(title)
	, m_pVLayout(Q_NULLPTR)
	, m_pTitleLabel(Q_NULLPTR)
{
	setMinimumSize(120, 120);
	setMaximumSize(120, 120);

	setFocusPolicy(Qt::ClickFocus); // 通过单击获取焦点事件
	setAttribute(Qt::WA_StyledBackground, true);// 自定义控件样式表生效

	setStyleSheet("background-color:#3f3f3c");

	m_pVLayout = new QVBoxLayout(this);
	m_pVLayout->setMargin(0); // 设置外边距
	m_pVLayout->setSpacing(0);

	m_pTitleLabel = new QLabel(this);
	m_pTitleLabel->setMaximumHeight(30);// 设置最大高度
	m_pTitleLabel->setMinimumHeight(30);
	m_pTitleLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter); // 设置对齐
	m_pTitleLabel->setStyleSheet("background-color:#3f3f3c; font-size:20px; color:#ffffff; font-family: Microsoft YaHei");
	m_pTitleLabel->setText(m_title);

	m_pVLayout->addWidget(m_pTitleLabel);
}

KParamBox::~KParamBox()
{
}

void KParamBox::enterEvent(QEvent* event)
{
	setCursor(Qt::PointingHandCursor); // 设置鼠标样式
}

void KParamBox::leaveEvent(QEvent* event)
{
	setCursor(Qt::ArrowCursor); // 设置鼠标样式
}
