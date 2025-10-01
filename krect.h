#ifndef __K_RECT_H_
#define __K_RECT_H_

#include "kshape.h"

// -------------------------------------------------------
// krect.h
// �����ߣ� �ӻ���
// ����ʱ�䣺 2025/4/13
// ���������� ����
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