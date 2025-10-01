#ifndef __K_CIRCLE_H__
#define __K_CIRCLE_H__

#include "kshape.h"

// -------------------------------------------------------
// kcircle.h
// 创建者： 钟欢欢
// 创建时间： 2025/4/13
// 功能描述： 圆形
// Copyright 2025 Kingsoft
// --------------------------------------------------------

class KCircle : public KShape
{
	Q_OBJECT

public:
	explicit KCircle(QObject* parent = Q_NULLPTR);
	~KCircle();

	virtual void drawShape(QPaintDevice* parent = Q_NULLPTR) override;
	virtual void drawSave(QPainter& painter) override;
	virtual KShapeType getShapeType() override;
};
#endif


