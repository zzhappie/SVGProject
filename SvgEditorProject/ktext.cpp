#include "ktext.h"
#include "kglobaldata.h"

#include <qcoreevent.h>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QLineEdit>
#include <QDebug>

KText::KText(QObject* parent)
	: KShape(parent)
	, m_pTextEdit(new QLineEdit(Q_NULLPTR))
	, m_isEditing(false)
	, m_initText("Please enter the content here!")
{
	m_pTextEdit->hide();
	m_pTextEdit->setText(m_initText);
	m_pTextEdit->installEventFilter(this);

	connect(m_pTextEdit, &QLineEdit::editingFinished, this, &KText::finishEditing);
}

KText::~KText()
{
	delete m_pTextEdit;
}

void KText::drawShape(QPaintDevice* parent)
{
	QPainter painter(parent);
	painter.setRenderHint(QPainter::Antialiasing);

	// 与画布一起缩放
	QTransform transform;
	qreal scaleFactor = KGlobalData::getGlobalDataIntance()->getCanvasScale();
	transform.scale(scaleFactor, scaleFactor);
	painter.setTransform(transform);

	QPen pen;
	pen.setColor(getBorderColor());
	pen.setStyle(getPenStyle());
	pen.setWidth(getBorderWidth());

	QBrush brush(getFillColor()); // 获取填充颜色
	painter.setBrush(brush);
	painter.setPen(pen);

	m_boundingRect = getCorrectBoundingbox();
	int fontSize = calculateFontSizeForRect(QRect(getStartPoint(), getEndPoint()));
	if (m_isEditing == true)
	{
		m_pTextEdit->setGeometry(m_boundingRect);
		m_pTextEdit->show();
		m_pTextEdit->setFocus();
		m_pTextEdit->setStyleSheet("border: 1px dashed black;");
		QFont editFont = m_pTextEdit->font();
		editFont.setPointSize(fontSize);  // 使用与绘制文本相同的字体大小
		m_pTextEdit->setFont(editFont);
	}
	else
	{
		QFont font = painter.font();
		font.setPointSize(fontSize);
		painter.setFont(font);
		painter.drawText(QRect(getStartPoint(), getEndPoint()), Qt::AlignCenter, m_pTextEdit->text());
	}
}

void KText::drawSave(QPainter& painter)
{
	QPen pen;
	pen.setColor(getBorderColor());
	pen.setStyle(getPenStyle());
	pen.setWidth(getBorderWidth());

	QBrush brush(getFillColor()); // 获取填充颜色
	painter.setBrush(brush);

	painter.setPen(pen);

	m_boundingRect = getCorrectBoundingbox();

	int fontSize = calculateFontSizeForRect(QRect(getStartPoint(), getEndPoint()));

	if (m_isEditing == true)
	{
		m_pTextEdit->setGeometry(m_boundingRect);
		m_pTextEdit->show();
		m_pTextEdit->setFocus();
		m_pTextEdit->setStyleSheet("border: 1px dashed black;");
	}
	else
	{
		QFont font = painter.font();
		font.setPointSize(fontSize);
		painter.setFont(font);
		painter.drawText(QRect(getStartPoint(), getEndPoint()), Qt::AlignCenter, m_pTextEdit->text());
	}
}

void KText::setEditing()
{
	m_isEditing = true;
}

void KText::setText()
{
	m_pTextEdit->setText(m_initText);
}

void KText::setEditParent(QWidget* parent)
{
	m_pTextEdit->setParent(parent);
}


KShapeType KText::getShapeType()
{
	return KShapeType::TextShapeType;
}

bool KText::isValid()
{
	return !m_pTextEdit->text().isEmpty();
}

bool KText::eventFilter(QObject* watched, QEvent* event)
{
	if (watched == m_pTextEdit)
	{
		if(event->type() == QEvent::KeyPress)
		{
			QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
			if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
			{
				m_pTextEdit->editingFinished();
				return true;
			}
			else
			{
				return false;
			}
		}
		if (event->type() == QEvent::FocusOut) // 设置焦点事件，当点击其他位置，自动隐藏关闭
		{
			m_pTextEdit->editingFinished();
			return true;
		}
	}
	return KShape::eventFilter(watched, event);
}

void KText::startEditing(const QPoint& pos, QWidget *parent)
{
	int width = 300;
	int height = 50;

	m_pTextEdit->setParent(parent);
	m_isEditing = true;
	m_centerPoint = pos / KGlobalData::getGlobalDataIntance()->getCanvasScale();
	m_pCurShapeParams->m_startPoint = QPoint(m_centerPoint.x() - width / 2, m_centerPoint.y() - height / 2);
	m_pCurShapeParams->m_endPoint = QPoint(m_centerPoint.x() + width / 2, m_centerPoint.y() + height / 2);
}

void KText::finishEditing()
{
	m_isEditing = false;
	m_pTextEdit->hide();
}

QRect KText::getCorrectBoundingbox()
{
	QPoint left = m_pCurShapeParams->m_startPoint * KGlobalData::getGlobalDataIntance()->getCanvasScale();
	QPoint right = m_pCurShapeParams->m_endPoint * KGlobalData::getGlobalDataIntance()->getCanvasScale();
	if (left.y() > right.y() && left.x() < right.x())
	{
		return QRect(QPoint(left.x(), right.y()),
			QPoint(right.x(), left.y()));
	}
	if (left.x() > right.x() && left.y() < right.y())
	{
		return QRect(QPoint(right.x(), left.y()),
			QPoint(left.x(), right.y()));
	}
	if (left.x() > right.x() && left.y() > right.y())
	{
		return QRect(QPoint(right.x(), right.y()),
			QPoint(left.x(), left.y()));
	}
	return QRect(left, right);
}

int KText::calculateFontSizeForRect(const QRectF& rect)
{
	qreal textHeightRatio = 0.3;
	int fontSize = static_cast<int>(qAbs(rect.height()) * textHeightRatio);
	if (fontSize < 8)
		fontSize = 8;
	return fontSize;
}

void KText::writeToStream(QDataStream& out) const
{
	out << m_pCurShapeParams->m_startPoint << m_pCurShapeParams->m_endPoint
		<< m_pCurShapeParams->m_borderWidth << m_pCurShapeParams->m_borderColor
		<< static_cast<int>(m_pCurShapeParams->m_penStyle) << m_pCurShapeParams->m_fillColor
		<< m_boundingRect << m_centerPoint << m_isEditing
		<< m_pTextEdit->text();
}

void KText::readFromStream(QDataStream& in)
{
	int penStyleInt;
	in >> m_pCurShapeParams->m_startPoint >> m_pCurShapeParams->m_endPoint
		>> m_pCurShapeParams->m_borderWidth >> m_pCurShapeParams->m_borderColor
		>> penStyleInt >> m_pCurShapeParams->m_fillColor
		>> m_boundingRect >> m_centerPoint >> m_isEditing
		>> m_initText;
	m_pCurShapeParams->m_penStyle = static_cast<Qt::PenStyle>(penStyleInt);
}
