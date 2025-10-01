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

    // 绘制心形
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

    // 绘制心形
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

    // 获取起点和终点
    QPointF startPoint = getStartPoint();
    QPointF endPoint = getEndPoint();

    // 计算心形的宽度和高度
    qreal width = endPoint.x() - startPoint.x();
    qreal height = endPoint.y() - startPoint.y();

    // 计算心形的中心点
    QPointF center(startPoint.x() + width / 2, startPoint.y() + height / 4);

    // 移动到心形的左上圆弧起点
    path.moveTo(startPoint.x(), startPoint.y() + 3 * height / 8);

    // 绘制左上圆弧
    path.cubicTo(
        startPoint.x() + width / 16, startPoint.y() + height / 16, // 控制点1
        startPoint.x() + 3 * width / 8, startPoint.y() + height / 12, // 控制点2
        center.x(), center.y());                 // 终点

    // 绘制右上圆弧
    path.cubicTo(
        startPoint.x() + 5 * width / 8, startPoint.y() + height / 16, // 控制点1
        startPoint.x() + 15 * width / 16, startPoint.y() + height / 12, // 控制点2
        endPoint.x(), startPoint.y() + 3 * height / 8);                   // 终点

    // 绘制右下曲线
    path.cubicTo(
        startPoint.x() + 15 * width / 16, startPoint.y() + 19 * height / 24, // 控制点1
        startPoint.x() + 5 * width / 8, startPoint.y() + 11 * height / 12 ,// 控制点2
        center.x(), endPoint.y());                 // 终点

    // 绘制左下曲线并闭合路径
    path.cubicTo(
        startPoint.x() + 3 * width / 8, startPoint.y() + 11 * height / 12, // 控制点1
        startPoint.x() + 1 * width / 16, startPoint.y() + 19 * height / 24,// 控制点2
        startPoint.x(), startPoint.y() + 3 * height / 8);                   // 终点（闭合）

    return path;
}


