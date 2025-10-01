#ifndef __K_PEN_H__
#define __K_PEN_H__

#include <QObject>

#include "kshape.h"

// -------------------------------------------------------
// kpen.h
// 创建者： 钟欢欢
// 创建时间： 2025/4/13
// 功能描述： 铅笔自由线
// Copyright 2025 Kingsoft
// --------------------------------------------------------

class KPen : public KShape
{
	Q_OBJECT

public:
	explicit KPen(QObject *parent = Q_NULLPTR);
	~KPen();

	virtual void drawShape(QPaintDevice* parent = Q_NULLPTR) override;
	virtual void drawSave(QPainter& painter) override; // 保存图形时绘制
	virtual KShapeType getShapeType() override;

	virtual void writeToStream(QDataStream& out) const override;
	virtual void readFromStream(QDataStream& in) override;

	virtual void move(QPoint offset) override;
	void penMove(QPoint offset);

	void addPos(const QPoint& pos);

private:
	QVector<QPoint> m_currentPath;
};
#endif
