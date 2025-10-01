#include "ksvgmainwindow.h"
#include "kclipboard.h"
#include "kshapeparascommand.h"
#include "kdeleteshapecommand.h"
#include "kaddshapecommand.h"
#include "kcanvasmenu.h"

#include <QApplication>
#include <QWheelEvent>
#include <QDebug>
#include <QGraphicsItem>

KSvgMainWindow::KSvgMainWindow(QWidget *parent)
	: QScrollArea(parent)
	, m_pCanvas(Q_NULLPTR)
{
	setFrameShape(QFrame::NoFrame); // 设置无边框

	// 当内容超过显示区域时出现滚动条
	setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	setStyleSheet("KSvgMainWindow{background-color:#3f3f3c;}");
	setAlignment(Qt::AlignCenter);
	
	m_pCanvas = new KCanvas(this);
	setWidget(m_pCanvas);// 设置当前控件为滚动区域的子控件
	m_pCanvas->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_canvasMenu = new KCanvasMenu(this);
	initCanvasMenuConnection();
	initPenCursor();
}

KSvgMainWindow::~KSvgMainWindow()
{
	delete m_pCanvas;
	delete m_canvasMenu;
}

void KSvgMainWindow::initCanvasMenuConnection()
{
	connect(m_canvasMenu->m_selectAllAct, &QAction::triggered, this, &KSvgMainWindow::selectAllShape);
	connect(m_canvasMenu->m_cutAct, &QAction::triggered, this, &KSvgMainWindow::cutCurrentShape);
	connect(m_canvasMenu->m_copyAct, &QAction::triggered, this, &KSvgMainWindow::copyCurrentShape);
	connect(m_canvasMenu->m_pasteAct, &QAction::triggered, this, &KSvgMainWindow::pasteCurrentShape);
	connect(m_canvasMenu->m_deleteAct, &QAction::triggered, this, &KSvgMainWindow::deleteCurrentShape);
	connect(m_canvasMenu->m_upLayerAct, &QAction::triggered, this, &KSvgMainWindow::upLayer);
	connect(m_canvasMenu->m_downLayerAct, &QAction::triggered, this, &KSvgMainWindow::downLayer);
	connect(m_canvasMenu->m_upTopLayerAct, &QAction::triggered, this, &KSvgMainWindow::upFrontLayer);
	connect(m_canvasMenu->m_downBottomLayerAct, &QAction::triggered, this, &KSvgMainWindow::downBackLayer);
	connect(m_canvasMenu->m_undoAct, &QAction::triggered, this, &KSvgMainWindow::shapeUndo);
	connect(m_canvasMenu->m_redoAct, &QAction::triggered, this, &KSvgMainWindow::shapeRedo);
	connect(m_pCanvas, &KCanvas::isSelectedShape, this, [this]()
		{
			m_canvasMenu->m_isSelectedShape = true;
		});
}

void KSvgMainWindow::initPenCursor()
{
	QPixmap penPixmap(":/ksvgmainwindow/icons/pen_cursor.png");
	QPoint hotSpot(0, penPixmap.height());
	penCursor = QCursor(penPixmap, hotSpot.x(), hotSpot.y());
}

void KSvgMainWindow::setCursorStyle(KButtonFlag buttonFlag)
{
	switch (buttonFlag)
	{
	case KButtonFlag::PenButtonFlag:
		setCursor(penCursor);
		break;
	case KButtonFlag::LineButtonFlag:
	case KButtonFlag::RectButtonFlag:
	case KButtonFlag::CircleButtonFlag:
	case KButtonFlag::PentButtonFlag:
	case KButtonFlag::HexaButtonFlag:
	case KButtonFlag::StarButtonFlag:
	case KButtonFlag::HeartButtonFlag:
	case KButtonFlag::BubbleButtonFlag:
		setCursor(Qt::CrossCursor);
		break;
	case KButtonFlag::TextButtonFlag:
		setCursor(Qt::IBeamCursor);
		break;
	default:
		setCursor(Qt::ArrowCursor);
		break;
	}
}

void KSvgMainWindow::enterEvent(QEvent* event)
{
	KButtonFlag flag = KGlobalData::getGlobalDataIntance()->getButtonFlag();
	setCursorStyle(flag);
	QScrollArea::enterEvent(event);
}

void KSvgMainWindow::wheelEvent(QWheelEvent* event)
{
	KButtonFlag flag = KGlobalData::getGlobalDataIntance()->getButtonFlag();
	if (flag == KButtonFlag::ZoomButtonFlag)
	{
		// 获取当前缩放比例
		qreal currentScale = KGlobalData::getGlobalDataIntance()->getCanvasScale();

		// 计算新的缩放比例（限制范围）
		const qreal SCALE_STEP = 0.05;
		const qreal MAX_SCALE = 10.0;
		const qreal MIN_SCALE = 0.1;

		qreal newScale = event->delta() > 0
			? currentScale + SCALE_STEP
			: currentScale - SCALE_STEP;

		newScale = qBound(MIN_SCALE, newScale, MAX_SCALE); // 限制缩放范围

		if (qFuzzyCompare(newScale, currentScale)) return; // 避免微小变化

		// 获取鼠标在画布上的位置（作为缩放中心）
		QPointF mousePos = m_pCanvas->mapFromGlobal(event->globalPos());

		// 计算缩放前后的尺寸
		qint32 oldWidth = KGlobalData::getGlobalDataIntance()->getCanvasWidth();
		qint32 oldHeight = KGlobalData::getGlobalDataIntance()->getCanvasHeight();
		qint32 newWidth = oldWidth * newScale;
		qint32 newHeight = oldHeight * newScale;

		// 调整画布位置，保持鼠标点在画布上的相对位置不变
		QPointF centerBefore = mousePos;
		QPointF centerAfter = centerBefore * (newScale / currentScale);
		QPointF offset = centerAfter - centerBefore;

		// 更新画布大小和位置
		m_pCanvas->resize(newWidth, newHeight);
		m_pCanvas->move(m_pCanvas->pos() - offset.toPoint());

		// 更新全局数据并通知其他组件
		KGlobalData::getGlobalDataIntance()->setCanvaScale(newScale);
		emit scaleChanged(newScale);

		//QGraphicsView::scale(newScale, newScale);

		m_pCanvas->update();
	}
}

void KSvgMainWindow::selectAllShape()
{
	m_pCanvas->m_isSelectedShapeList.clear();
	for (auto shape : m_pCanvas->m_pShapeList)
	{
		m_pCanvas->m_isSelectedShapeList.push_back(shape);
	}
}

void KSvgMainWindow::cutCurrentShape()
{
	m_pCanvas->m_pClipBoard->copy(m_pCanvas->m_isSelectedShapeList);
	deleteCurrentShape(); // 删除，可以直接撤退
}

void KSvgMainWindow::copyCurrentShape()
{
	m_pCanvas->m_pClipBoard->copy(m_pCanvas->m_isSelectedShapeList);
}

void KSvgMainWindow::pasteCurrentShape()
{
	for (auto shape : m_pCanvas->m_pClipBoard->getData(m_pCanvas->m_clickedPos, m_pCanvas))
	{
		m_pCanvas->m_pShapeList.append(shape);
		m_pCanvas->m_pCurrentShape = shape;

		KGlobalData::getGlobalDataIntance()->getUndoStack()->push(new KAddShapeCommand(m_pCanvas->m_pCurrentShape,
			&m_pCanvas->m_pShapeList, &m_pCanvas->m_pdeletedShapeList));
	}
	update();
}

void KSvgMainWindow::copyAndPasteCurrentShape()
{
	copyCurrentShape();
	pasteCurrentShape();
}

void KSvgMainWindow::deleteCurrentShape()
{
	// 删除图形的时候，把绘制列表的指针移除，内存由删除图形列表管理，最后析构时完成释放
	if (!m_pCanvas->m_isSelectedShapeList.isEmpty())
	{
		for (auto shape : m_pCanvas->m_isSelectedShapeList)
		{
			m_pCanvas->m_pShapeList.removeOne(shape);
			KGlobalData::getGlobalDataIntance()->getUndoStack()->push(new KDeleteShapeCommand(&m_pCanvas->m_isSelectedShapeList, 
				&m_pCanvas->m_pShapeList,&m_pCanvas->m_pdeletedShapeList));
			if (m_pCanvas->m_pShapeList.isEmpty()) {
				emit canvasChosen();
 			}
		}
	}
	m_pCanvas->m_isSelectedShapeList.clear();
	m_pCanvas->update();
}

void KSvgMainWindow::keyPressEvent(QKeyEvent* event)
{
	QWidget::keyReleaseEvent(event);
	// 检查并处理快捷键  
	if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_A && m_canvasMenu->m_selectAllAct && m_canvasMenu->m_selectAllAct->isEnabled())
		m_canvasMenu->m_selectAllAct->trigger(); // Ctrl+A 全选  

	if (event->matches(QKeySequence::Undo) && m_canvasMenu->m_undoAct && m_canvasMenu->m_undoAct->isEnabled())
		m_canvasMenu->m_undoAct->trigger(); // 撤销  

	if (event->matches(QKeySequence::Redo) && m_canvasMenu->m_redoAct && m_canvasMenu->m_redoAct->isEnabled())
		m_canvasMenu->m_redoAct->trigger(); // 重做  

	if (event->matches(QKeySequence::Cut) && m_canvasMenu->m_cutAct && m_canvasMenu->m_cutAct->isEnabled())
		m_canvasMenu->m_cutAct->trigger(); // 剪切  

	if (event->matches(QKeySequence::Copy) && m_canvasMenu->m_copyAct && m_canvasMenu->m_copyAct->isEnabled())
		m_canvasMenu->m_copyAct->trigger(); // 复制  

	if (event->matches(QKeySequence::Paste) && m_canvasMenu->m_pasteAct && m_canvasMenu->m_pasteAct->isEnabled())
		m_canvasMenu->m_pasteAct->trigger(); // 粘贴    

	if (event->key() == Qt::Key_Delete && m_canvasMenu->m_deleteAct && m_canvasMenu->m_deleteAct->isEnabled())
		m_canvasMenu->m_deleteAct->trigger(); // 删除  

	if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Up && m_canvasMenu->m_upLayerAct && m_canvasMenu->m_upLayerAct->isEnabled())
		m_canvasMenu->m_upLayerAct->trigger(); // Ctrl+Up 置上一层  

	if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Down && m_canvasMenu->m_downLayerAct && m_canvasMenu->m_downLayerAct->isEnabled())
		m_canvasMenu->m_downLayerAct->trigger(); // Ctrl+Down 置下一层  

	if (event->modifiers() == (Qt::ControlModifier | Qt::ShiftModifier) && event->key() == Qt::Key_Up && m_canvasMenu->m_upTopLayerAct && m_canvasMenu->m_upTopLayerAct->isEnabled())
		m_canvasMenu->m_upTopLayerAct->trigger(); // Ctrl+Shift+Up 置于顶层  

	if (event->modifiers() == (Qt::ControlModifier | Qt::ShiftModifier) && event->key() == Qt::Key_Down && m_canvasMenu->m_downBottomLayerAct && m_canvasMenu->m_downBottomLayerAct->isEnabled())
		m_canvasMenu->m_downBottomLayerAct->trigger(); // Ctrl+Shift+Down 置于底层 
	update();
}

void KSvgMainWindow::upLayer()
{
	int index = m_pCanvas->findShapeIndex(m_pCanvas->m_pCurrentShape);
	if (index != -1)
	{
		if (index < m_pCanvas->m_pShapeList.size() && index > 0)
		{
			m_pCanvas->m_pShapeList.swap(index, index - 1);
		}
	}
}

void KSvgMainWindow::downLayer()
{
	int index = m_pCanvas->findShapeIndex(m_pCanvas->m_pCurrentShape);
	if (index != -1)
	{
		if (index < m_pCanvas->m_pShapeList.size() - 1 && index >= 0)
		{
			m_pCanvas->m_pShapeList.swap(index, index + 1);
		}
	}
}

void KSvgMainWindow::upFrontLayer()
{
	int index = m_pCanvas->findShapeIndex(m_pCanvas->m_pCurrentShape);
	if (index != -1)
	{
		if (index < m_pCanvas->m_pShapeList.size() && index > 0)
		{
			m_pCanvas->m_pShapeList.insert(0, m_pCanvas->m_pShapeList.takeAt(index));
		}
	}
}

void KSvgMainWindow::downBackLayer()
{
	int index = m_pCanvas->findShapeIndex(m_pCanvas->m_pCurrentShape);
	if (index != -1)
	{
		if (index < m_pCanvas->m_pShapeList.size() - 1 && index >= 0)
		{
			m_pCanvas->m_pShapeList.append(m_pCanvas->m_pShapeList.takeAt(index));
		}
	}
}

void KSvgMainWindow::shapeUndo()
{
	m_pCanvas->m_isSelectedShapeList.clear();
	KGlobalData::getGlobalDataIntance()->getUndoStack()->undo();
	emit m_pCanvas->canvasParamsChanged();
}

void KSvgMainWindow::shapeRedo()
{
	KGlobalData::getGlobalDataIntance()->getUndoStack()->redo();
	emit m_pCanvas->canvasParamsChanged();
}