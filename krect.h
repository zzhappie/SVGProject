#ifndef __K_RECT_H_
#define __K_RECT_H_

#include "kshape.h"

// -------------------------------------------------------
// krect.h
// 创建者： 钟欢欢
// 创建时间： 2025/4/13
// 功能描述： 矩形
// Copyright 2025 Kingsoft
// --------------------------------------------------------

class KRect : public KShape
{
	Q_OBJECT

public:
	explicit KRect(QObject *parent = Q_NULLPTR);
	~KRect();

	virtual void drawShape(QPaintDevice* parent = Q_NULLPTR) override;
	virtual void drawSave(QPainter& painter) override;
	virtual KShapeType getShapeType() override;
};
#endif