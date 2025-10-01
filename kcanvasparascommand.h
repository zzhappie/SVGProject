#ifndef __K_CANVAS_PARAS_COMMAND_H__
#define __K_CANVAS_PARAS_COMMAND_H__

#include <QUndoCommand>

#include "kglobaldata.h"

// -------------------------------------------------------
// kcanvasparascommand.h
// 创建者： 钟欢欢
// 创建时间： 2025/5/17
// 功能描述： 画布参数的redo、undo命令
// Copyright 2025 Kingsoft
// --------------------------------------------------------

class KCanvasParasCommand : public QUndoCommand
{
public:
	KCanvasParasCommand(KCanvasParams* canvasParams, QUndoCommand* parent = Q_NULLPTR);
	~KCanvasParasCommand();

	virtual void undo() override;
	virtual void redo() override;
private:
	KCanvasParams* m_canvasParams;
};
#endif


