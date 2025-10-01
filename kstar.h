#ifndef ___K_STAR_H__
#define ___K_STAR_H__

#include "kshape.h"

// -------------------------------------------------------
// kstar.h
// 创建者： 钟欢欢
// 创建时间： 2025/4/14
// 功能描述： 五角星
// Copyright 2025 Kingsoft
// --------------------------------------------------------

class KStar : public KShape
{
	Q_OBJECT

public:
	explicit KStar(QObject* parent = Q_NULLPTR);
	~KStar();

	virtual void drawShape(QPaintDevice* parent = Q_NULLPTR) override;
	virtual void drawSave(QPainter& painter) override;
	virtual KShapeType getShapeType() override;

private:
	QPolygonF generateStar();
};
#endif