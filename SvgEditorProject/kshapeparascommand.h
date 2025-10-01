#ifndef __K_SHAPE_PARAS_COMMAND_H__
#define __K_SHAPE_PARAS_COMMAND_H__

#include <QUndoCommand>
#include "kshape.h"

// -------------------------------------------------------
// kshapeparascommand.h
// 创建者： 钟欢欢
// 创建时间： 2025/5/19
// 功能描述： 图形参数的redo，undo命令
// Copyright 2025 Kingsoft
// --------------------------------------------------------

class KShapeParasCommand : public QUndoCommand
{
public:
	KShapeParasCommand(std::shared_ptr<KShapeParams> shapeParms, KShape* shape = Q_NULLPTR, QUndoCommand* parent = Q_NULLPTR);
	~KShapeParasCommand();

	virtual void undo() override;
	virtual void redo() override;

private:
	KShape* m_shape;
	std::shared_ptr<KShapeParams> m_prevShapeParams;
	std::shared_ptr<KShapeParams> m_curShapeParams;
};
#endif