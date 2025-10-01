#ifndef __K_PEN_H__
#define __K_PEN_H__

#include <QObject>

#include "kshape.h"

// -------------------------------------------------------
// kpen.h
// �����ߣ� �ӻ���
// ����ʱ�䣺 2025/4/13
// ���������� Ǧ��������
// Copyright 2025 Kingsoft
// --------------------------------------------------------

class KPen : public KShape
{
	Q_OBJECT

public:
	explicit KPen(QObject *parent = Q_NULLPTR);
	~KPen();

	virtual void drawShape(QPaintDevice* parent = Q_NULLPTR) override;
	virtual void drawSave(QPainter& painter) override; // ����ͼ��ʱ����
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
