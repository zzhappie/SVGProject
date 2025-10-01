#include "ktoolbutton.h"

#include <QToolTip>

KToolButton::KToolButton(KButtonFlag buttonflag, QWidget* parent)
	: QRadioButton(parent)
	, m_pSvgRenderer(nullptr)
	, m_buttonFlag(buttonflag)
{
	initToolButton();
}

KToolButton::~KToolButton()
{
}

void KToolButton::initToolButton()
{
	switch (m_buttonFlag)
	{
	case KButtonFlag::MouseButtonFlag:
		m_iconName = "mouse.svg";
		break;
	case KButtonFlag::PenButtonFlag:
		m_iconName = "pen.svg";
		break;
	case KButtonFlag::LineButtonFlag:
		m_iconName = "line.svg";
		break;
	case KButtonFlag::RectButtonFlag:
		m_iconName = "rectangle.svg";
		break;
	case KButtonFlag::CircleButtonFlag:
		m_iconName = "circle.svg";
		break;
	case KButtonFlag::PentButtonFlag:
		m_iconName = "pentagon.svg";
		break;
	case KButtonFlag::HexaButtonFlag:
		m_iconName = "hexagon.svg";
		break;
	case KButtonFlag::StarButtonFlag:
		m_iconName = "star.svg";
		break;
	case KButtonFlag::TextButtonFlag:
		m_iconName = "text.svg";
		break;
	case KButtonFlag::ZoomButtonFlag:
		m_iconName = "zoom.svg";
		break;
	case KButtonFlag::HeartButtonFlag:
		m_iconName = "heart.svg";
		break;
	case KButtonFlag::BubbleButtonFlag:
		m_iconName = "bubble.svg";
		break;
	default:
		break;
	}

	m_pSvgRenderer = new QSvgRenderer(":/icons/normal/" + m_iconName);
	this->setMinimumSize(50, 50);

	// ��ť�л�ʱ������onToggledButton()���д���
	(void)connect(this, &KToolButton::toggled, this, &KToolButton::onToggledButton);
}

void KToolButton::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	m_pSvgRenderer->render(&painter, QRectF(0, 0, 50, 50));
}

void KToolButton::enterEvent(QEvent* event)
{
	// �����ťδ��ѡ�У����� hover ��ͼ��
	if (!isChecked())
		m_pSvgRenderer->load(":/icons/hover/" + m_iconName);

	setCursor(Qt::PointingHandCursor); //���ù����ʽ

	QPair<QString, QString> tip = KGlobalData::getGlobalDataIntance()->getButtonTip(m_buttonFlag);
	if (!tip.first.isEmpty() || !tip.second.isEmpty()) {
		QString tooltipText = "<b>" + tip.first + "</b><br/>" + tip.second;
		QToolTip::showText(mapToGlobal(QPoint(width() / 2, height())), tooltipText, this);
	}

	update();// ������ͼ�¼�
}

void KToolButton::leaveEvent(QEvent* event)
{
	if (!isChecked())
		m_pSvgRenderer->load(":/icons/normal/" + m_iconName);

	setCursor(Qt::ArrowCursor);
	QToolTip::hideText();
	update();
}

void KToolButton::mouseReleaseEvent(QMouseEvent* e)
{
	setChecked(true);// ���õ�ǰ��ťΪѡ��״̬
}

void KToolButton::onToggledButton(bool checked)
{
	if (isChecked())
	{
		m_pSvgRenderer->load(":/icons/selected/" + m_iconName);
		KGlobalData::getGlobalDataIntance()->setButtonFlag(m_buttonFlag);
	}
	else
		m_pSvgRenderer->load(":/icons/normal/" + m_iconName);
	update();
}