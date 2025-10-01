#include "kcanvasparascommand.h"
#include "kglobaldata.h"

KCanvasParasCommand::KCanvasParasCommand(KCanvasParams* canvasParams, QUndoCommand* parent)
	: QUndoCommand(parent)
	, m_canvasParams(canvasParams)
{
	KGlobalData::getGlobalDataIntance()->setPrevCanvasWidth(m_canvasParams->m_canvasWidth);
	KGlobalData::getGlobalDataIntance()->setPrevCanvasHeight(m_canvasParams->m_canvasHeight);
	KGlobalData::getGlobalDataIntance()->setPrevCanvasColor(m_canvasParams->m_canvasColor);
}

KCanvasParasCommand::~KCanvasParasCommand()
{
}

void KCanvasParasCommand::undo()
{
	KGlobalData::getGlobalDataIntance()->setCanvasWidth(m_canvasParams->m_prevCanvasWidth);
	KGlobalData::getGlobalDataIntance()->setCanvasHeight(m_canvasParams->m_prevCanvasHeight);
	KGlobalData::getGlobalDataIntance()->setCanvasColor(m_canvasParams->m_prevCanvasColor);
	KGlobalData::getGlobalDataIntance()->setPrevCanvasWidth(m_canvasParams->m_prevCanvasWidth);
	KGlobalData::getGlobalDataIntance()->setPrevCanvasHeight(m_canvasParams->m_prevCanvasHeight);
	KGlobalData::getGlobalDataIntance()->setPrevCanvasColor(m_canvasParams->m_prevCanvasColor);
}

void KCanvasParasCommand::redo()
{
	KGlobalData::getGlobalDataIntance()->setCanvasWidth(m_canvasParams->m_canvasWidth);
	KGlobalData::getGlobalDataIntance()->setCanvasHeight(m_canvasParams->m_canvasHeight);
	KGlobalData::getGlobalDataIntance()->setCanvasColor(m_canvasParams->m_canvasColor);
	KGlobalData::getGlobalDataIntance()->setPrevCanvasWidth(m_canvasParams->m_canvasWidth);
	KGlobalData::getGlobalDataIntance()->setPrevCanvasHeight(m_canvasParams->m_canvasHeight);
	KGlobalData::getGlobalDataIntance()->setPrevCanvasColor(m_canvasParams->m_canvasColor);
}
