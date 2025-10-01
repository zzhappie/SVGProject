#ifndef __K_DELETE_SHAPE_COMMAND_H__
#define __K_DELETE_SHAPE_COMMAND_H__

#include <QUndoCommand>

// -------------------------------------------------------
// kdeleteshapecommand.h
// 创建者： 钟欢欢
// 创建时间： 2025/5/13
// 功能描述： 删除图形的undo、 redo命令
// Copyright 2025 Kingsoft
// --------------------------------------------------------

class KShape;

class KDeleteShapeCommand : public QUndoCommand
{
public:
	KDeleteShapeCommand(QList<KShape*>* isSelectedShapelist, QList<KShape*>* shapelist, QList<KShape*>* deletedShapeList, QUndoCommand* parent = Q_NULLPTR);
	~KDeleteShapeCommand();

	virtual void undo() override;
	virtual void redo() override;

private:
	QList<KShape*>* m_isSelectedShapelist;
	QList<KShape*>* m_shapeList;
	QList<KShape*>* m_deletedShapeList;
	QList<KShape*> m_record;
};
#endif


