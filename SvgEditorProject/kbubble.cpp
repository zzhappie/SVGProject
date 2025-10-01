#include "kbubble.h"
#include <QPainterPath>

#include "kglobaldata.h"

KBubble::KBubble(QObject *parent)
	: KShape(parent)
{
}

KBubble::~KBubble()
{
}

void KBubble::drawShape(QPaintDevice* parent)
{
    QPainter painter(parent);
    painter.setRenderHint(QPainter::Antialiasing);

    // �뻭��һ������
    QTransform transform;
    qreal scaleFactor = KGlobalData::getGlobalDataIntance()->getCanvasScale();
    transform.scale(scaleFactor, scaleFactor);
    painter.setTransform(transform);

    QPen pen;
    pen.setColor(getBorderColor());
    pen.setStyle(getPenStyle());
    pen.setWidth(getBorderWidth());

    QBrush brush(getFillColor());
    painter.setBrush(brush);
    painter.setPen(pen);

    QPainterPath path = calculateBubblePath();
    painter.drawPath(path);
}

void KBubble::drawSave(QPainter& painter)
{
    QPen pen;
    pen.setColor(getBorderColor());
    pen.setStyle(getPenStyle());
    pen.setWidth(getBorderWidth());

    QBrush brush(getFillColor());
    painter.setBrush(brush);
    painter.setPen(pen);

    QPainterPath path = calculateBubblePath();
    painter.drawPath(path);
}

KShapeType KBubble::getShapeType()
{
    return KShapeType::BubbleShapeType;
}

QPainterPath KBubble::calculateBubblePath()
{
    QPointF startPoint = getStartPoint();
    QPointF endPoint = getEndPoint();

    // �������ݿ�Ŀ�Ⱥ͸߶�
    qreal width = endPoint.x() - startPoint.x();
    qreal height = endPoint.y() - startPoint.y();

    // ����С�����εĸ߶�
    qreal triangleHeight = height / 4;
    qreal radius = width / 10; // Բ�ǰ뾶

    QPainterPath path;

    // ����Բ�Ǿ�����ʼ�㣨���½ǣ�
    path.moveTo(startPoint.x(), endPoint.y() - triangleHeight - radius);
    // ����Բ�Ǿ������
    path.lineTo(startPoint.x(), startPoint.y() + radius);
    // �������Ͻ�Բ��
    path.arcTo(startPoint.x(), startPoint.y(), 2 * radius, 2 * radius, 180, -90);
    // �����ϱ�
    path.lineTo(endPoint.x() - radius, startPoint.y());
    // �������Ͻ�Բ��
    path.arcTo(endPoint.x() - 2 * radius, startPoint.y(), 2 * radius, 2 * radius, 90, -90);
    // �����ұ�
    path.lineTo(endPoint.x(), endPoint.y() - triangleHeight - radius);
    // �������½�Բ��
    path.arcTo(endPoint.x() - 2 * radius, endPoint.y()- triangleHeight - 2 * radius, 2 * radius, 2 * radius, 0, -90);
    // �����±߾����Ҷ�
    path.lineTo(startPoint.x() + 2 * width / 5, endPoint.y() - triangleHeight);
    // ����С�������ұ�
    path.lineTo(startPoint.x() + width / 8, endPoint.y());
    // ����С���������
    path.lineTo(startPoint.x() + width / 6, endPoint.y() - triangleHeight);
    // �����±߾������
    path.lineTo(startPoint.x()+ radius, endPoint.y() - triangleHeight);
    // �������½�Բ��
    path.arcTo(startPoint.x(), endPoint.y() - triangleHeight - 2 * radius, 2 * radius, 2 * radius, 270, -90);

    // �պ�·��
    path.closeSubpath();

    return path;
}




