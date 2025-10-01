#include "kshapefactory.h"

#include "kpen.h"
#include "kline.h"
#include "krect.h"
#include "kcircle.h"
#include "kpent.h"
#include "khexa.h"
#include "kstar.h"
#include "ktext.h"
#include "kheart.h"
#include "kbubble.h"

KShapeFactory::KShapeFactory(QObject *parent)
	: QObject(parent)
{
}

KShapeFactory::~KShapeFactory()
{
}

KShape* KShapeFactory::createShape(KButtonFlag buttonFlag)
{
	switch(buttonFlag)
	{
	case KButtonFlag::PenButtonFlag:
		return new KPen;
	case KButtonFlag::LineButtonFlag:
		return new KLine;
	case KButtonFlag::RectButtonFlag:
		return new KRect;
	case KButtonFlag::CircleButtonFlag:
		return new KCircle;
	case KButtonFlag::PentButtonFlag:
		return new KPent;
	case KButtonFlag::HexaButtonFlag:
		return new KHexa;
	case KButtonFlag::StarButtonFlag:
		return new KStar;
	case KButtonFlag::TextButtonFlag:
		return new KText;
	case KButtonFlag::HeartButtonFlag:
		return new KHeart;
	case KButtonFlag::BubbleButtonFlag:
		return new KBubble;
	default:
		return Q_NULLPTR;
	}
}
