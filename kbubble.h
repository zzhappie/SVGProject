#ifndef __K_BUBBLE_H__
#define __K_BUBBLE_H__

#include "kshape.h"

#include <QObject>

// -------------------------------------------------------
// kbubble.h
// 创建者： 钟欢欢
// 创建时间： 2025/4/15
// 功能描述： 气泡框
// Copyright 2025 Kingsoft
// --------------------------------------------------------

class KBubble  : public KShape
{
	Q_OBJECT

public:
	explicit KBubble(QObject* parent = Q_NULLPTR);
	~KBubble();

	virtual void drawShape(QPaintDevice* parent = Q_NULLPTR) override;
	void drawSave(QPainter& painter) override;
	virtual KShapeType getShapeType() override;

private:
	QPainterPath calculateBubblePath();
};
#endif
