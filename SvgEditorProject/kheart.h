#ifndef __K_HEART_H__
#define __K_HEART_H__

#include "kshape.h"

#include <QObject>

// -------------------------------------------------------
// kheart.h
// 创建者： 钟欢欢
// 创建时间： 2025/4/15
// 功能描述： 爱心
// Copyright 2025 Kingsoft
// --------------------------------------------------------

class KHeart  : public KShape
{
	Q_OBJECT

public:
	explicit KHeart(QObject* parent = Q_NULLPTR);
	~KHeart();

	virtual void drawShape(QPaintDevice* parent = Q_NULLPTR) override;
	void drawSave(QPainter& painter) override;
	virtual KShapeType getShapeType() override;

private:
	QPainterPath calculateHeartPath();
};
#endif
