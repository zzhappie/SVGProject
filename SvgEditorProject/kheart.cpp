#include "kheart.h"
#include <QPainterPath>

#include "kglobaldata.h"

KHeart::KHeart(QObject* parent)
    : KShape(parent)
{
}

KHeart::~KHeart()
{
}

void KHeart::drawShape(QPaintDevice* parent)
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

    // ��������
    QPainterPath path = calculateHeartPath();
    painter.drawPath(path);
}

void KHeart::drawSave(QPainter& painter)
{
    QPen pen;
    pen.setColor(getBorderColor());
    pen.setStyle(getPenStyle());
    pen.setWidth(getBorderWidth());

    QBrush brush(getFillColor());
    painter.setBrush(brush);
    painter.setPen(pen);

    // ��������
    QPainterPath path = calculateHeartPath();
    painter.drawPath(path);
}


KShapeType KHeart::getShapeType()
{
    return KShapeType::HeartShapeType;
}

QPainterPath KHeart::calculateHeartPath()
{
    QPainterPath path;

    // ��ȡ�����յ�
    QPointF startPoint = getStartPoint();
    QPointF endPoint = getEndPoint();

    // �������εĿ�Ⱥ͸߶�
    qreal width = endPoint.x() - startPoint.x();
    qreal height = endPoint.y() - startPoint.y();

    // �������ε����ĵ�
    QPointF center(startPoint.x() + width / 2, startPoint.y() + height / 4);

    // �ƶ������ε�����Բ�����
    path.moveTo(startPoint.x(), startPoint.y() + 3 * height / 8);

    // ��������Բ��
    path.cubicTo(
        startPoint.x() + width / 16, startPoint.y() + height / 16, // ���Ƶ�1
        startPoint.x() + 3 * width / 8, startPoint.y() + height / 12, // ���Ƶ�2
        center.x(), center.y());                 // �յ�

    // ��������Բ��
    path.cubicTo(
        startPoint.x() + 5 * width / 8, startPoint.y() + height / 16, // ���Ƶ�1
        startPoint.x() + 15 * width / 16, startPoint.y() + height / 12, // ���Ƶ�2
        endPoint.x(), startPoint.y() + 3 * height / 8);                   // �յ�

    // ������������
    path.cubicTo(
        startPoint.x() + 15 * width / 16, startPoint.y() + 19 * height / 24, // ���Ƶ�1
        startPoint.x() + 5 * width / 8, startPoint.y() + 11 * height / 12 ,// ���Ƶ�2
        center.x(), endPoint.y());                 // �յ�

    // �����������߲��պ�·��
    path.cubicTo(
        startPoint.x() + 3 * width / 8, startPoint.y() + 11 * height / 12, // ���Ƶ�1
        startPoint.x() + 1 * width / 16, startPoint.y() + 19 * height / 24,// ���Ƶ�2
        startPoint.x(), startPoint.y() + 3 * height / 8);                   // �յ㣨�պϣ�

    return path;
}


