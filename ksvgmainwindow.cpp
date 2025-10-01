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
	setFrameShape(QFrame::NoFrame); // �����ޱ߿�

	// �����ݳ�����ʾ����ʱ���ֹ�����
	setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	setStyleSheet("KSvgMainWindow{background-color:#3f3f3c;}");
	setAlignment(Qt::AlignCenter);
	
	m_pCanvas = new KCanvas(this);
	setWidget(m_pCanvas);// ���õ�ǰ�ؼ�Ϊ����������ӿؼ�
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
		// ��ȡ��ǰ���ű���
		qreal currentScale = KGlobalData::getGlobalDataIntance()->getCanvasScale();

		// �����µ����ű��������Ʒ�Χ��
		const qreal SCALE_STEP = 0.05;
		const qreal MAX_SCALE = 10.0;
		const qreal MIN_SCALE = 0.1;

		qreal newScale = event->delta() > 0
			? currentScale + SCALE_STEP
			: currentScale - SCALE_STEP;

		newScale = qBound(MIN_SCALE, newScale, MAX_SCALE); // �������ŷ�Χ

		if (qFuzzyCompare(newScale, currentScale)) return; // ����΢С�仯

		// ��ȡ����ڻ����ϵ�λ�ã���Ϊ�������ģ�
		QPointF mousePos = m_pCanvas->mapFromGlobal(event->globalPos());

		// ��������ǰ��ĳߴ�
		qint32 oldWidth = KGlobalData::getGlobalDataIntance()->getCanvasWidth();
		qint32 oldHeight = KGlobalData::getGlobalDataIntance()->getCanvasHeight();
		qint32 newWidth = oldWidth * newScale;
		qint32 newHeight = oldHeight * newScale;

		// ��������λ�ã����������ڻ����ϵ����λ�ò���
		QPointF centerBefore = mousePos;
		QPointF centerAfter = centerBefore * (newScale / currentScale);
		QPointF offset = centerAfter - centerBefore;

		// ���»�����С��λ��
		m_pCanvas->resize(newWidth, newHeight);
		m_pCanvas->move(m_pCanvas->pos() - offset.toPoint());

		// ����ȫ�����ݲ�֪ͨ�������
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
	deleteCurrentShape(); // ɾ��������ֱ�ӳ���
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
	// ɾ��ͼ�ε�ʱ�򣬰ѻ����б��ָ���Ƴ����ڴ���ɾ��ͼ���б�����������ʱ����ͷ�
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
	// ��鲢�����ݼ�  
	if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_A && m_canvasMenu->m_selectAllAct && m_canvasMenu->m_selectAllAct->isEnabled())
		m_canvasMenu->m_selectAllAct->trigger(); // Ctrl+A ȫѡ  

	if (event->matches(QKeySequence::Undo) && m_canvasMenu->m_undoAct && m_canvasMenu->m_undoAct->isEnabled())
		m_canvasMenu->m_undoAct->trigger(); // ����  

	if (event->matches(QKeySequence::Redo) && m_canvasMenu->m_redoAct && m_canvasMenu->m_redoAct->isEnabled())
		m_canvasMenu->m_redoAct->trigger(); // ����  

	if (event->matches(QKeySequence::Cut) && m_canvasMenu->m_cutAct && m_canvasMenu->m_cutAct->isEnabled())
		m_canvasMenu->m_cutAct->trigger(); // ����  

	if (event->matches(QKeySequence::Copy) && m_canvasMenu->m_copyAct && m_canvasMenu->m_copyAct->isEnabled())
		m_canvasMenu->m_copyAct->trigger(); // ����  

	if (event->matches(QKeySequence::Paste) && m_canvasMenu->m_pasteAct && m_canvasMenu->m_pasteAct->isEnabled())
		m_canvasMenu->m_pasteAct->trigger(); // ճ��    

	if (event->key() == Qt::Key_Delete && m_canvasMenu->m_deleteAct && m_canvasMenu->m_deleteAct->isEnabled())
		m_canvasMenu->m_deleteAct->trigger(); // ɾ��  

	if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Up && m_canvasMenu->m_upLayerAct && m_canvasMenu->m_upLayerAct->isEnabled())
		m_canvasMenu->m_upLayerAct->trigger(); // Ctrl+Up ����һ��  

	if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Down && m_canvasMenu->m_downLayerAct && m_canvasMenu->m_downLayerAct->isEnabled())
		m_canvasMenu->m_downLayerAct->trigger(); // Ctrl+Down ����һ��  

	if (event->modifiers() == (Qt::ControlModifier | Qt::ShiftModifier) && event->key() == Qt::Key_Up && m_canvasMenu->m_upTopLayerAct && m_canvasMenu->m_upTopLayerAct->isEnabled())
		m_canvasMenu->m_upTopLayerAct->trigger(); // Ctrl+Shift+Up ���ڶ���  

	if (event->modifiers() == (Qt::ControlModifier | Qt::ShiftModifier) && event->key() == Qt::Key_Down && m_canvasMenu->m_downBottomLayerAct && m_canvasMenu->m_downBottomLayerAct->isEnabled())
		m_canvasMenu->m_downBottomLayerAct->trigger(); // Ctrl+Shift+Down ���ڵײ� 
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