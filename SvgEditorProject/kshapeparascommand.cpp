#include "kshapeparascommand.h"

KShapeParasCommand::KShapeParasCommand(std::shared_ptr<KShapeParams> shapeParms, KShape* shape, QUndoCommand* parent)
	: QUndoCommand(parent)
	, m_shape(shape)
	, m_prevShapeParams(shape->getPrevShapeParams()) //初始化前置状态，供本次的命令使用
	, m_curShapeParams(shapeParms)
{
	shape->setPrevShapeParams(); //每次创建新的command入栈的时候，把当前的shape参数设置前置状态。
}

KShapeParasCommand::~KShapeParasCommand()
{
}

void KShapeParasCommand::undo()
{
	m_shape->setCurShapeParams(m_prevShapeParams);
	m_shape->setPrevShapeParams();
}

void KShapeParasCommand::redo()
{
	m_shape->setCurShapeParams(m_curShapeParams);
	m_shape->setPrevShapeParams();
}
