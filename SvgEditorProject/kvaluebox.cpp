#include "kvaluebox.h"
#include <QRegExpValidator>

KValueBox::KValueBox(const QString &title,const qreal val,QWidget *parent)
	: KParamBox(title,parent)
	, m_pParamEdit(Q_NULLPTR)
{
	m_pParamEdit = new QLineEdit(this);
	m_pParamEdit->setText(QString::number(val));
	m_pParamEdit->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	m_pParamEdit->setStyleSheet("background-color:#3f3f3c; font-size:48px; color:#4f80ff; font-family:Times New Roman; font-weight: regular; border-width:0; border-style:outset");
	m_pParamEdit->setMaxLength(4);

	QRegExp reg("[2-9][0-9]*|[1-9][0-9]+$"); // ������ʽ  ��Ϊ���ܴ���1�Ĳ���
	QValidator* validator = new QRegExpValidator(reg, m_pParamEdit);
	m_pParamEdit->setValidator(validator); // ����������ʽ

	m_pVLayout->addWidget(m_pParamEdit);// ���뵽������ m_pVLayout �����ڸ�����
}

KValueBox::~KValueBox()
{
}

void KValueBox::focusInEvent(QFocusEvent* event)
{
	m_pParamEdit->selectAll();// ȫѡ�ı�
}
