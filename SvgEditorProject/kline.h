#ifndef __K_LINE_H__
#define __K_LINE_H__

#include "kshape.h"

// -------------------------------------------------------
// kline.h
// 创建者： 钟欢欢
// 创建时间： 2025/4/13
// 功能描述： 直线
// Copyright 2025 Kingsoft
// --------------------------------------------------------

class KLine : public KShape
{
	Q_OBJECT

public:
	explicit KLine(QObject* parent = Q_NULLPTR);
	~KLine();

	virtual void drawShape(QPaintDevice* parent = Q_NULLPTR) override;
	virtual void drawSave(QPainter& painter) override;
	virtual KShapeType getShapeType() override;
};

#endif


