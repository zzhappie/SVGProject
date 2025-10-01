#include "krect.h"
#include "kglobaldata.h"

#include <QPainter>
#include <QSvgGenerator>

KRect::KRect(QObject *parent)
	: KShape(parent)
{
}

KRect::~KRect()
{
}

void KRect::drawShape(QPaintDevice* parent)
{
	QPainter painter(parent);

	// �뻭��һ������
	QTransform transform;
	qreal scaleFactor = KGlobalData::getGlobalDataIntance()->getCanvasScale();
	transform.scale(scaleFactor, scaleFactor);
	painter.setTransform(transform);

	QPen pen;
	pen.setColor(getBorderColor());
	pen.setStyle(getPenStyle());
	pen.setWidth(getBorderWidth());

	QBrush brush(getFillColor()); // ��ȡ�����ɫ
	painter.setBrush(brush);

	painter.setPen(pen);
	painter.drawRect(QRect(getStartPoint(),getEndPoint()));
}

void KRect::drawSave(QPainter& painter)
{
	QPen pen;
	pen.setColor(getBorderColor());
	pen.setStyle(getPenStyle());
	pen.setWidth(getBorderWidth());

	QBrush brush(getFillColor()); // ��ȡ�����ɫ
	painter.setBrush(brush);

	painter.setPen(pen);
	painter.drawRect(QRect(getStartPoint(), getEndPoint()));
	
}

KShapeType KRect::getShapeType()
{
	return KShapeType::RectShapeType;
}
