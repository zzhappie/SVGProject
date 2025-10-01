#include "kparambox.h"

KParamBox::KParamBox(const QString &title,QWidget *parent)
	: QWidget(parent)
	, m_title(title)
	, m_pVLayout(Q_NULLPTR)
	, m_pTitleLabel(Q_NULLPTR)
{
	setMinimumSize(120, 120);
	setMaximumSize(120, 120);

	setFocusPolicy(Qt::ClickFocus); // ͨ��������ȡ�����¼�
	setAttribute(Qt::WA_StyledBackground, true);// �Զ���ؼ���ʽ����Ч

	setStyleSheet("background-color:#3f3f3c");

	m_pVLayout = new QVBoxLayout(this);
	m_pVLayout->setMargin(0); // ������߾�
	m_pVLayout->setSpacing(0);

	m_pTitleLabel = new QLabel(this);
	m_pTitleLabel->setMaximumHeight(30);// �������߶�
	m_pTitleLabel->setMinimumHeight(30);
	m_pTitleLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter); // ���ö���
	m_pTitleLabel->setStyleSheet("background-color:#3f3f3c; font-size:20px; color:#ffffff; font-family: Microsoft YaHei");
	m_pTitleLabel->setText(m_title);

	m_pVLayout->addWidget(m_pTitleLabel);
}

KParamBox::~KParamBox()
{
}

void KParamBox::enterEvent(QEvent* event)
{
	setCursor(Qt::PointingHandCursor); // ���������ʽ
}

void KParamBox::leaveEvent(QEvent* event)
{
	setCursor(Qt::ArrowCursor); // ���������ʽ
}
