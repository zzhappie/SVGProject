#ifndef __K_SHAPEFACTORY_H__
#define __K_SHAPEFACTORY_H__

#include <QObject>

#include "kglobaldata.h"
#include "kshape.h"

// -------------------------------------------------------
// kshapefactory.h
// 创建者： 钟欢欢
// 创建时间： 2025/4/15
// 功能描述： 图形制造工厂
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
