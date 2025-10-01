#ifndef __K_CLIPBOARD_H__
#define __K_CLIPBOARD_H__

#include "kglobaldata.h"
#include "kshape.h"

#include <QObject>
#include <QClipboard>
#include <QGuiApplication>

// -------------------------------------------------------
// kclipboard.h
// 创建者： 钟欢欢
// 创建时间： 2025/4/22
// 功能描述： 复制、剪切、粘贴。
// Copyright 2025 Kingsoft
// --------------------------------------------------------

class KShapeClipboard : public QObject
{
    Q_OBJECT

public:
    KShapeClipboard(QObject* parent = Q_NULLPTR);
    ~KShapeClipboard();

    void copy(QList<KShape*>& shapeList);
    bool contains();
    QList<KShape*> getData(const QPoint& point,QWidget* parent);
    void clear();

private:
    void switchType(KShapeType shapeType);

    QClipboard* m_pClipboard;
    KShapeType m_shapeType;
    KButtonFlag m_buttonFlag;

    bool isSigleShape;
};
#endif