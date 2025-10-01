#ifndef __K_TEXT_H__
#define __K_TEXT_H__

#include <QLineEdit>

#include "kshape.h"

// -------------------------------------------------------
// ktext.h
// 创建者： 钟欢欢
// 创建时间： 2025/4/15
// 功能描述： 文本框输入
// Copyright 2025 Kingsoft
// --------------------------------------------------------

class KText : public KShape
{
	Q_OBJECT
public:
	explicit KText(QObject* parent = Q_NULLPTR);
	~KText();

	virtual void drawShape(QPaintDevice* parent) override;
	virtual void drawSave(QPainter& painter) override;
	virtual void writeToStream(QDataStream& out) const override;
	virtual void readFromStream(QDataStream& in) override;

	virtual KShapeType getShapeType() override;
	virtual bool isValid() override;
	bool eventFilter(QObject* watched, QEvent* event) override;
	void startEditing(const QPoint& pos, QWidget* parent); // 开始编辑文本
	void setEditing();
	void setText();
	void setEditParent(QWidget* parent);

private:
	QRect m_boundingRect; // 文本框的矩形范围
	QPoint m_centerPoint; //中心位置
	QLineEdit* m_pTextEdit; // 文本输入框
	QString m_initText;
	bool m_isEditing; // 是否正在编辑文本
	void finishEditing(); // 结束编辑文本
	QRect getCorrectBoundingbox();
	int calculateFontSizeForRect(const QRectF& rect);
};
#endif