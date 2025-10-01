#include "kdeleteshapecommand.h"

KDeleteShapeCommand::KDeleteShapeCommand(QList<KShape*>* isSelectedShapelist, QList<KShape*>* shapelist, QList<KShape*>* deletedShapeList, QUndoCommand* parent)
	: QUndoCommand(parent)
	, m_isSelectedShapelist(isSelectedShapelist)
	, m_shapeList(shapelist)
	, m_deletedShapeList(deletedShapeList)
{
	// 存储要删除形状的本地副本，用于跟踪操作历史
	for (KShape* shape : *isSelectedShapelist)
	{
		m_record.append(shape);
	}
}

KDeleteShapeCommand::~KDeleteShapeCommand()
{
}

void KDeleteShapeCommand::undo()
{
	
	for (auto shape : m_record)
	{
		if (!m_shapeList->contains(shape))
		{
			m_shapeList->prepend(shape);
		}
		m_deletedShapeList->removeOne(shape);
	}
}

void KDeleteShapeCommand::redo()
{
	for (auto shape : m_record)
	{
		m_shapeList->removeOne(shape);
		if (!m_deletedShapeList->contains(shape))
		{
			m_deletedShapeList->append(shape);
		}
	}
}
