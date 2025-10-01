#include "kcircle.h"
#include "kglobaldata.h"

#include <QPainter>
#include <QSvgGenerator>

KCircle::KCircle(QObject* parent)
	:KShape(parent)
{
}

KCircle::~KCircle()
{
}

void KCircle::drawShape(QPaintDevice* parent)
{
	QPainter painter(parent);
	painter.setRenderHint(QPainter::Antialiasing);  // 抗锯齿

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
	painter.drawEllipse(QRect(getStartPoint(), getEndPoint()));
}

void KCircle::drawSave(QPainter& painter)
{
	QPen pen;
	pen.setColor(getBorderColor());
	pen.setStyle(getPenStyle());
	pen.setWidth(getBorderWidth());

	QBrush brush(getFillColor()); // 获取填充颜色
	painter.setBrush(brush);

	painter.setPen(pen);
	painter.drawEllipse(QRect(getStartPoint(), getEndPoint()));
	
}

KShapeType KCircle::getShapeType()
{
	return KShapeType::CircleShapeType;
}
