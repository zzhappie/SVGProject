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

    // 与画布一起缩放
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

    // 计算气泡框的宽度和高度
    qreal width = endPoint.x() - startPoint.x();
    qreal height = endPoint.y() - startPoint.y();

    // 计算小三角形的高度
    qreal triangleHeight = height / 4;
    qreal radius = width / 10; // 圆角半径

    QPainterPath path;

    // 绘制圆角矩形起始点（左下角）
    path.moveTo(startPoint.x(), endPoint.y() - triangleHeight - radius);
    // 绘制圆角矩形左边
    path.lineTo(startPoint.x(), startPoint.y() + radius);
    // 绘制左上角圆角
    path.arcTo(startPoint.x(), startPoint.y(), 2 * radius, 2 * radius, 180, -90);
    // 绘制上边
    path.lineTo(endPoint.x() - radius, startPoint.y());
    // 绘制右上角圆角
    path.arcTo(endPoint.x() - 2 * radius, startPoint.y(), 2 * radius, 2 * radius, 90, -90);
    // 绘制右边
    path.lineTo(endPoint.x(), endPoint.y() - triangleHeight - radius);
    // 绘制右下角圆角
    path.arcTo(endPoint.x() - 2 * radius, endPoint.y()- triangleHeight - 2 * radius, 2 * radius, 2 * radius, 0, -90);
    // 绘制下边矩形右段
    path.lineTo(startPoint.x() + 2 * width / 5, endPoint.y() - triangleHeight);
    // 绘制小三角形右边
    path.lineTo(startPoint.x() + width / 8, endPoint.y());
    // 绘制小三角形左边
    path.lineTo(startPoint.x() + width / 6, endPoint.y() - triangleHeight);
    // 绘制下边矩形左段
    path.lineTo(startPoint.x()+ radius, endPoint.y() - triangleHeight);
    // 绘制左下角圆角
    path.arcTo(startPoint.x(), endPoint.y() - triangleHeight - 2 * radius, 2 * radius, 2 * radius, 270, -90);

    // 闭合路径
    path.closeSubpath();

    return path;
}




