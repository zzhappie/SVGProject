#include "kpen.h"
#include "kglobaldata.h"

#include <QPainterPath>

KPen::KPen(QObject *parent)
	: KShape(parent)
{
}

KPen::~KPen()
{
}

void KPen::drawShape(QPaintDevice* parent)
{
	QPainter painter(parent);
	painter.setRenderHint(QPainter::Antialiasing); // 抗锯齿

	// 与画布一起缩放
	QTransform transform;
	qreal scaleFactor = KGlobalData::getGlobalDataIntance()->getCanvasScale();
	transform.scale(scaleFactor, scaleFactor);
	painter.setTransform(transform);

	QPainterPath path;
	if (m_currentPath.isEmpty()) return;
	auto pos = m_currentPath.begin();

	path.moveTo(*pos);
	while (pos != m_currentPath.end())
	{
		path.lineTo(*pos);
		pos++;
	}

	QPen pen;
	pen.setColor(getBorderColor());
	pen.setWidthF(getBorderWidth());
	pen.setStyle(getPenStyle());
	painter.setPen(pen);
	painter.drawPath(path);
}

void KPen::drawSave(QPainter& painter)
{
	QPainterPath path;
	painter.setRenderHint(QPainter::Antialiasing);
	if (m_currentPath.isEmpty()) return;
	auto pos = m_currentPath.begin();

	path.moveTo(*pos);
	while (pos != m_currentPath.end())
	{
		path.lineTo(*pos);
		pos++;
	}

	QPen pen;
	pen.setColor(getBorderColor());
	pen.setWidthF(getBorderWidth());
	pen.setStyle(getPenStyle());
	painter.setPen(pen);
	painter.drawPath(path);
}

KShapeType KPen::getShapeType()
{
	return KShapeType::PenShapeType;
}

void KPen::writeToStream(QDataStream& out) const
{
	out << m_pCurShapeParams->m_startPoint << m_pCurShapeParams->m_endPoint
		<< m_pCurShapeParams->m_borderWidth << m_pCurShapeParams->m_borderColor
		<< static_cast<int>(m_pCurShapeParams->m_penStyle) << m_pCurShapeParams->m_fillColor
		<< m_currentPath;
}

void KPen::readFromStream(QDataStream& in)
{
	int penStyleInt;
	in >> m_pCurShapeParams->m_startPoint >> m_pCurShapeParams->m_endPoint
		>> m_pCurShapeParams->m_borderWidth >> m_pCurShapeParams->m_borderColor
		>> penStyleInt >> m_pCurShapeParams->m_fillColor
		>> m_currentPath;
	m_pCurShapeParams->m_penStyle = static_cast<Qt::PenStyle>(penStyleInt);
}

void KPen::move(QPoint offset)
{
	for (int i = 0; i < m_currentPath.size(); ++i)
	{
		m_currentPath[i] += offset;
	}
	KShape::move(offset);
}

void KPen::penMove(QPoint offset)
{
	for (int i = 0; i < m_currentPath.size(); ++i)
	{
		m_currentPath[i] += offset;
	}
}

// 添加一个新的坐标点，并根据添加点的位置更新图形参数
void KPen::addPos(const QPoint& pos)
{
	if (m_currentPath.isEmpty())
	{
		m_pCurShapeParams->m_startPoint = pos;
		m_pCurShapeParams->m_endPoint = pos;
	}
	else
	{
		if (pos.x() < m_pCurShapeParams->m_startPoint.x())
			m_pCurShapeParams->m_startPoint.rx() = pos.x();
		if (pos.y() < m_pCurShapeParams->m_startPoint.y())
			m_pCurShapeParams->m_startPoint.ry() = pos.y();
		if (pos.x() > m_pCurShapeParams->m_endPoint.x())
			m_pCurShapeParams->m_endPoint.rx() = pos.x();
		if (pos.y() > m_pCurShapeParams->m_endPoint.y())
			m_pCurShapeParams->m_endPoint.ry() = pos.y();
	}
	m_currentPath.append(pos);
}