#include "kshape.h"
#include "kglobaldata.h"

#include <QDebug>

KShape::KShape(QObject *parent)
	: QObject(parent)
	,m_pCurShapeParams(new KShapeParams)
	,m_pPrevShapeParams(new KShapeParams)
{
	m_pCurShapeParams->m_borderWidth = KGlobalData::getGlobalDataIntance()->getBorderWidth();
	m_pCurShapeParams->m_penStyle = KGlobalData::getGlobalDataIntance()->getPenStyle();
	m_pCurShapeParams->m_borderColor = KGlobalData::getGlobalDataIntance()->getBoderColor();
	m_pCurShapeParams->m_fillColor = KGlobalData::getGlobalDataIntance()->getFillColor();
}

KShape::~KShape()
{
}

void KShape::move(QPoint offset)
{
	m_pCurShapeParams->m_startPoint += offset;
	m_pCurShapeParams->m_endPoint += offset;
}

void KShape::moveTop(QPoint pos)
{
	m_pCurShapeParams->m_startPoint.ry() = pos.y();
}

void KShape::moveBottom(QPoint pos)
{
	m_pCurShapeParams->m_endPoint.ry() = pos.y();
}

void KShape::moveLeft(QPoint pos)
{
	m_pCurShapeParams->m_startPoint.rx() = pos.x();
}

void KShape::moveRight(QPoint pos)
{
	m_pCurShapeParams->m_endPoint.rx() = pos.x();
}

void KShape::moveTopLeft(QPoint pos)
{
	m_pCurShapeParams->m_startPoint = pos;
}

void KShape::moveTopRight(QPoint pos)
{
	m_pCurShapeParams->m_startPoint.ry() = pos.y();
	m_pCurShapeParams->m_endPoint.rx() = pos.x();
}

void KShape::moveBottomLeft(QPoint pos)
{
	m_pCurShapeParams->m_startPoint.rx() = pos.x();
	m_pCurShapeParams->m_endPoint.ry() = pos.y();
}

void KShape::moveBottomRight(QPoint pos)
{
	m_pCurShapeParams->m_endPoint = pos;
}

void KShape::writeToStream(QDataStream& out) const
{
	out << m_pCurShapeParams->m_startPoint << m_pCurShapeParams->m_endPoint
		<< m_pCurShapeParams->m_borderWidth << m_pCurShapeParams->m_borderColor
		<< static_cast<int>(m_pCurShapeParams->m_penStyle) << m_pCurShapeParams->m_fillColor;
}

void KShape::readFromStream(QDataStream& in)
{
	int penStyleInt;
	in >> m_pCurShapeParams->m_startPoint >> m_pCurShapeParams->m_endPoint
		>> m_pCurShapeParams->m_borderWidth >> m_pCurShapeParams->m_borderColor
		>> penStyleInt >> m_pCurShapeParams->m_fillColor;
	m_pCurShapeParams->m_penStyle = static_cast<Qt::PenStyle>(penStyleInt);
}

QPoint KShape::getStartPoint()
{
	return m_pCurShapeParams->m_startPoint;
}

void KShape::setStartPoint(const QPoint& point)
{
	m_pCurShapeParams->m_startPoint = point;
	qDebug() << QString::fromLocal8Bit("设置起始点： ") << m_pCurShapeParams->m_startPoint;
}

QPoint KShape::getEndPoint()
{
	return m_pCurShapeParams->m_endPoint;
}

void KShape::setEndPoint(const QPoint& point)
{
	m_pCurShapeParams->m_endPoint = point;
	qDebug() << QString::fromLocal8Bit("设置结束点： ") << m_pCurShapeParams->m_endPoint;
}

int KShape::getWidth() const
{
	return qAbs(m_pCurShapeParams->m_startPoint.x() - m_pCurShapeParams->m_endPoint.x());
}

void KShape::setWidth(const int w)
{
	m_pCurShapeParams->m_width = w;
}

int KShape::getHeight() const
{
	return qAbs(m_pCurShapeParams->m_startPoint.y() - m_pCurShapeParams->m_endPoint.y());
}

void KShape::setHeight(const int h)
{
	m_pCurShapeParams->m_height = h;
}

int KShape::getBorderWidth() const
{
	return m_pCurShapeParams->m_borderWidth;
}

void KShape::setBorderWidth(const int value)
{
	m_pCurShapeParams->m_borderWidth = value;
}

QColor KShape::getBorderColor() const
{
	return m_pCurShapeParams->m_borderColor;
}

void KShape::setBorderColor(QColor color)
{
	m_pCurShapeParams->m_borderColor = color;
}

Qt::PenStyle KShape::getPenStyle() const
{
	return m_pCurShapeParams->m_penStyle;
}

void KShape::setPenStyle(Qt::PenStyle style)
{
	m_pCurShapeParams->m_penStyle = style;
}

QColor KShape::getFillColor() const
{
	return m_pCurShapeParams->m_fillColor;
}

void KShape::setFillColor(QColor color)
{
	m_pCurShapeParams->m_fillColor = color;
}

void KShape::drawRectOutLine(QPaintDevice* parent)
{
	QPainter painter(parent);
	QPen pen;

	pen.setColor(QColor(79, 128, 255));
	pen.setWidth(3);
	painter.setPen(pen);

	qreal scaleFactor = KGlobalData::getGlobalDataIntance()->getCanvasScale();
	painter.scale(scaleFactor, scaleFactor); // 对绘图缩放，以适应当前画布的缩放设置
	painter.drawRect(QRect(getStartPoint(), getEndPoint()));
}

QRect KShape::getOutLineRect() const
{
	return QRect(m_pCurShapeParams->m_startPoint, m_pCurShapeParams->m_endPoint);
}

bool KShape::isValid()
{
	return (m_pCurShapeParams->m_startPoint.x() != m_pCurShapeParams->m_endPoint.x() || m_pCurShapeParams->m_startPoint.y() != m_pCurShapeParams->m_endPoint.y());
}

std::shared_ptr<KShapeParams> KShape::getCurShapeParams()
{
	m_pCurShapeParams->m_height = getHeight();
	m_pCurShapeParams->m_width = getWidth();
	return m_pCurShapeParams;
}

void KShape::setCurShapeParams(std::shared_ptr<KShapeParams> shapeParams)
{
	m_pCurShapeParams = shapeParams;
}

std::shared_ptr<KShapeParams> KShape::getPrevShapeParams()
{
	return m_pPrevShapeParams;
}

void KShape::setPrevShapeParams()
{
	m_pPrevShapeParams = m_pCurShapeParams;
}