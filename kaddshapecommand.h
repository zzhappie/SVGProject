#ifndef __K_ADD_SHAPE_COMMAND_H__
#define __K_ADD_SHAPE_COMMAND_H__

#include <QUndoCommand>

// -------------------------------------------------------
// kaddshapecommand.h
// 创建者： 钟欢欢
// 创建时间： 2025/5/10
// 功能描述： 添加图形的undo、redo命令
// Copyright 2025 Kingsoft
// --------------------------------------------------------

class KShape;

class KAddShapeCommand : public QUndoCommand
{
public:
	KAddShapeCommand(KShape* createdShape, QList<KShape*>* shapelist, QList<KShape*>* deletedShapeList, QUndoCommand* parent = Q_NULLPTR);
	~KAddShapeCommand();

	virtual void undo() override;
	virtual void redo() override;

private:
	KShape* m_curCreatedShape;
	QList<KShape*>* m_shapeList;
	QList<KShape*>* m_deletedShapeList;
	KShape* m_record;
};
#endif


