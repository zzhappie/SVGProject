#ifndef __K_SHAPE_H__
#define __K_SHAPE_H__

#include <QObject>
#include <QPainter>
#include <QPaintDevice>
#include <memory>

#include "kglobaldata.h"

// -------------------------------------------------------
// kshape.h
// 创建者： 钟欢欢
// 创建时间： 2025/4/13
// 功能描述： 绘图基类
// Copyright 2025 Kingsoft
// --------------------------------------------------------

class KShape : public QObject
{
	Q_OBJECT
public:
	explicit KShape(QObject *parent = Q_NULLPTR);
	~KShape();

	// 在子类中重写，实现不同类型的图形的绘制
	virtual void drawShape(QPaintDevice* parent = Q_NULLPTR) = 0;
	virtual void drawSave(QPainter& painter) = 0; // 保存使用
	virtual KShapeType getShapeType() = 0;

	virtual void move(QPoint offset);
	virtual void moveTop(QPoint pos);
	virtual void moveBottom(QPoint pos);
	virtual void moveLeft(QPoint pos);
	virtual void moveRight(QPoint pos);
	virtual void moveTopLeft(QPoint pos);
	virtual void moveTopRight(QPoint pos);
	virtual void moveBottomLeft(QPoint pos);
	virtual void moveBottomRight(QPoint pos);

	// 重载运算符，用于将KShape数据写入到 QDataStream,方便复制粘贴。
	virtual void writeToStream(QDataStream& out) const;
	virtual void readFromStream(QDataStream& in);
	friend QDataStream& operator<<(QDataStream& out, const KShape& shape)
	{
		shape.writeToStream(out);
		return out;
	}

	friend QDataStream& operator>>(QDataStream& in, KShape& shape)
	{
		shape.readFromStream(in);
		return in;
	}

	QPoint getStartPoint();
	void setStartPoint(const QPoint& point);

	QPoint getEndPoint();
	void setEndPoint(const QPoint& point);

	int getWidth() const;
	void setWidth(const int w);

	int getHeight() const;
	void setHeight(const int h);

	// 画笔
	int getBorderWidth() const;
	void setBorderWidth(const int value);

	QColor getBorderColor() const;
	void setBorderColor(QColor color);

	Qt::PenStyle getPenStyle() const;
	void setPenStyle(Qt::PenStyle style);

	QColor getFillColor() const;
	void setFillColor(QColor color);

	// 选中矩形框
	void drawRectOutLine(QPaintDevice* parent = Q_NULLPTR);
	QRect getOutLineRect() const;
	virtual bool isValid();

	std::shared_ptr<KShapeParams> getCurShapeParams();
	void setCurShapeParams(std::shared_ptr<KShapeParams> shapeParams);

	std::shared_ptr<KShapeParams> getPrevShapeParams();
	void setPrevShapeParams();

protected:
	std::shared_ptr<KShapeParams> m_pPrevShapeParams; // 存储前置状态，撤回使用
	std::shared_ptr<KShapeParams> m_pCurShapeParams; // 存储当前状态
};
#endif
