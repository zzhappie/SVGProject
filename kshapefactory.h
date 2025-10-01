#ifndef __K_SHAPEFACTORY_H__
#define __K_SHAPEFACTORY_H__

#include <QObject>

#include "kglobaldata.h"
#include "kshape.h"

// -------------------------------------------------------
// kshapefactory.h
// �����ߣ� �ӻ���
// ����ʱ�䣺 2025/4/15
// ���������� ͼ�����칤��
// Copyright 2025 Kingsoft
// --------------------------------------------------------

class KShapeFactory : public QObject
{
	Q_OBJECT
public:
	explicit KShapeFactory(QObject *parent = Q_NULLPTR);
	~KShapeFactory();

	static KShape* createShape(KButtonFlag buttonFlag);
};
#endif
