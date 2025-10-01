#ifndef __K_HEXA_H__
#define __K_HEXA_H__

#include "kshape.h"

// -------------------------------------------------------
// khexa.h
// 创建者： 钟欢欢
// 创建时间： 2025/4/14
// 功能描述： 六边形
// Copyright 2025 Kingsoft
// --------------------------------------------------------

class KHexa : public KShape
{
	Q_OBJECT

public:
	explicit KHexa(QObject* parent = Q_NULLPTR);
	~KHexa();

	virtual void drawShape(QPaintDevice* parent = Q_NULLPTR) override;
	void drawSave(QPainter& painter) override;
	virtual KShapeType getShapeType() override;

private:
	QPolygonF calculateHexaPoints();
};
#endif