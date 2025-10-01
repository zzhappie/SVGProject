#ifndef __K_PENT_H__
#define __K_PENT_H__

#include "kshape.h"

// -------------------------------------------------------
// kpent.h
// 创建者： 钟欢欢
// 创建时间： 2025/4/14
// 功能描述： 五边形
// Copyright 2025 Kingsoft
// --------------------------------------------------------

class KPent : public KShape
{
    Q_OBJECT

public:
    explicit KPent(QObject* parent = Q_NULLPTR);
    virtual ~KPent();

    virtual void drawShape(QPaintDevice* parent = Q_NULLPTR) override;
    virtual void drawSave(QPainter& painter) override;
    virtual KShapeType getShapeType() override;

private:
    QPolygonF calculatePentagonPoints();
};
#endif

