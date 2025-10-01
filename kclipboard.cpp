#include "kclipboard.h"

#include "kpen.h"
#include "kshape.h"
#include "kshapefactory.h"
#include "ktext.h"

#include <QDataStream>
#include <QMimeData>

KShapeClipboard::KShapeClipboard(QObject* parent)
	: QObject(parent)
	, isSigleShape(false)
{
    m_pClipboard = QGuiApplication::clipboard();
}

KShapeClipboard::~KShapeClipboard()
{
}

void KShapeClipboard::copy(QList<KShape*>& shapeList)
{
    if (shapeList.size() == 1)
        isSigleShape = true;
    else
        isSigleShape = false;
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);

    for (KShape* shape : shapeList)
    {
        dataStream << static_cast<int>(shape->getShapeType());
        dataStream << *shape;
    }
    QMimeData* mimeData = new QMimeData;
    mimeData->setData("application/x-kshape", itemData);
    m_pClipboard->setMimeData(mimeData);
}

bool KShapeClipboard::contains()
{
    const QMimeData* mimeData = m_pClipboard->mimeData();
    return mimeData->hasFormat("application/x-kshape");
}

QList<KShape*> KShapeClipboard::getData(const QPoint& point,QWidget* parent)
{
    const QMimeData* mimeData = m_pClipboard->mimeData();
    if (mimeData->hasFormat("application/x-kshape")) 
    {
        QByteArray itemData = mimeData->data("application/x-kshape");

        if (itemData.isEmpty())
            return {}; // 如果数据为空，直接返回空

        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QList<KShape*> shapeList;
        while (!dataStream.atEnd())
        {
            int ishapeType;
            dataStream >> ishapeType;

            KShapeType shapeType = static_cast<KShapeType>(ishapeType);
            switchType(shapeType);

            KShape* pShape = KShapeFactory::createShape(m_buttonFlag);
            dataStream >> *pShape; //读取信息

            if (isSigleShape == false)
            {
                pShape->setStartPoint(pShape->getStartPoint() + QPoint(20,20));
                pShape->setEndPoint(pShape->getEndPoint() + QPoint(20, 20));

                if (pShape->getShapeType() == KShapeType::PenShapeType)
                {
                    pShape->move(QPoint(20, 20));
                }
            }
            else
            {
                double width = qAbs(pShape->getEndPoint().x() - pShape->getStartPoint().x());
                double height = qAbs(pShape->getStartPoint().y() - pShape->getEndPoint().y());

                // 根据点击鼠标位置，计算新的左上角点和右下角点坐标
                QPoint newLeftTop;
                QPoint newRightBottom;
                newLeftTop.rx() = point.x() - width / 2;
                newLeftTop.ry() = point.y() - height / 2;
                newRightBottom.rx() = point.x() + width / 2;
                newRightBottom.ry() = point.y() + height / 2;

                if (pShape->getShapeType() == KShapeType::PenShapeType)
                {
                    QPoint offset = newLeftTop - pShape->getStartPoint();
                    qobject_cast<KPen*>(pShape)->penMove(offset);
                }
                pShape->setStartPoint(newLeftTop);
                pShape->setEndPoint(newRightBottom);
            }

            if (pShape->getShapeType() == KShapeType::TextShapeType)
            {
                qobject_cast<KText*>(pShape)->setEditing();
                qobject_cast<KText*>(pShape)->setText();
                qobject_cast<KText*>(pShape)->setEditParent(parent);
            }

            shapeList.append(pShape);
        }
        return shapeList;
    }
    return {};
}

void KShapeClipboard::clear()
{
    m_pClipboard->clear();
}

void KShapeClipboard::switchType(KShapeType shapeType)
{
    switch (shapeType)
    {
    case KShapeType::PenShapeType:
        m_buttonFlag = KButtonFlag::PenButtonFlag;
        break;
    case KShapeType::LineShapeType:
        m_buttonFlag = KButtonFlag::LineButtonFlag;
        break;
    case KShapeType::CircleShapeType:
        m_buttonFlag = KButtonFlag::CircleButtonFlag;
        break;
    case KShapeType::RectShapeType:
        m_buttonFlag = KButtonFlag::RectButtonFlag;
        break;
    case KShapeType::PentShapeType:
        m_buttonFlag = KButtonFlag::PentButtonFlag;
        break;
    case KShapeType::HexaShapeType:
        m_buttonFlag = KButtonFlag::HexaButtonFlag;
        break;
    case KShapeType::StarShapeType:
        m_buttonFlag = KButtonFlag::StarButtonFlag;
        break;
    case KShapeType::HeartShapeType:
        m_buttonFlag = KButtonFlag::HeartButtonFlag;
        break;
    case KShapeType::BubbleShapeType:
        m_buttonFlag = KButtonFlag::BubbleButtonFlag;
        break;
    case KShapeType::TextShapeType:
        m_buttonFlag = KButtonFlag::TextButtonFlag;
        break;
    }
}
