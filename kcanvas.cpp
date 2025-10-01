#include "kcanvas.h"
#include "kshapefactory.h"
#include "kpen.h"
#include "ktext.h"
#include "kshapeparascommand.h"
#include "kaddshapecommand.h"

#include <QMouseEvent>
#include <QDebug>
#include <QSvgGenerator>
#include <QMessageBox>
#include <QSvgRenderer>
#include <QFileDialog>
#include <QShortcut>

KCanvas::KCanvas(QWidget* parent)
	: QWidget(parent)
	, m_renderer(Q_NULLPTR)
	, m_pCurrentShape(Q_NULLPTR)
	, m_TransType(KTransType::None)
	, m_isDrawing(false)
	, m_isLPress(false)
	, m_isSelected(false)
	, m_isRender(false)
	, m_pClipBoard(new KShapeClipboard(this))
{
	setAttribute(Qt::WA_StyledBackground, true);
	// ���ñ�����ɫΪ��ɫ
	setStyleSheet("KCanvas{background-color:#ffffff;}");
	KGlobalData::getGlobalDataIntance()->setCanvasColor("FFFFFF");

	resize(KGlobalData::getGlobalDataIntance()->getCanvasWidth(),
		KGlobalData::getGlobalDataIntance()->getCanvasHeight());
	setStyleSheet("KCanvas{background-color:#ffffff;}");

	setMouseTracking(true);//�������׷��
	setFocusPolicy(Qt::ClickFocus);// ������ȡ����
}

KCanvas::~KCanvas()
{
	for (auto shape : m_pShapeList)
		delete shape;
	for (auto shape : m_pdeletedShapeList)
		delete shape;
	m_pShapeList.clear();
	m_pdeletedShapeList.clear();
	m_pClipBoard->clear(); // ������ʱ��������а�
}

void KCanvas::createCanvas()
{
	QMessageBox::StandardButton reply;
	reply = QMessageBox::question(this, QString::fromLocal8Bit("�½�����"), QString::fromLocal8Bit("ȷ���½���������ע��˲�������յ�ǰ���ݣ�"),
		QMessageBox::Yes | QMessageBox::No);
	if (reply == QMessageBox::No)
		return;

	// �ͷ��ڴ�
	for (auto shape : m_pShapeList)
		delete shape;
	for (auto shape : m_pdeletedShapeList)
		delete shape;
	m_pShapeList.clear();
	m_pdeletedShapeList.clear();
	m_isSelectedShapeList.clear();
	KGlobalData::getGlobalDataIntance()->getUndoStack()->clear();
	m_pClipBoard->clear();

	delete m_renderer;
	m_renderer = Q_NULLPTR;
	update();
}

void KCanvas::loadSvg()
{
	QString fileName = QFileDialog::getOpenFileName(this,
		QString::fromLocal8Bit("ѡ��SVG�ļ�"),
		"", // Ĭ��Ŀ¼����Ϊ�գ�����ָ��һ����ʼĿ¼  
		"SVG �ļ� (*.svg);;�����ļ� (*.*)"); // �ļ�������  

	if (fileName.isEmpty())
		return;

	if (m_renderer == Q_NULLPTR)
		m_renderer = new QSvgRenderer(this);

	if (!m_pShapeList.isEmpty())
	{
		for (auto shape : m_pShapeList)
			delete shape;
		m_pShapeList.clear();
	}

	// ���� SVG �ļ�
	m_renderer->load(fileName);
	if (!m_renderer->isValid())
	{
		qDebug() << "Error: SVG file is invalid or could not be loaded.";
		return;
	}

	// ���»��ƴ���
	update();
}

void KCanvas::saveToSvg()
{
	QString fileName = QFileDialog::getSaveFileName(nullptr, QString::fromLocal8Bit("����ΪSVG�ļ�"), "svg.svg");
	if (fileName.isEmpty())
		return;

	QString svgBackgroundColor = KGlobalData::getGlobalDataIntance()->getCanvasColor();

	// ���� QSvgGenerator ��������
	QSvgGenerator svgGenerator;
	svgGenerator.setFileName(fileName);
	svgGenerator.setSize(QSize(KGlobalData::getGlobalDataIntance()->getCanvasWidth(), 
		KGlobalData::getGlobalDataIntance()->getCanvasHeight()));  // ���� SVG ͼ���С
	svgGenerator.setViewBox(QRect(0, 0, KGlobalData::getGlobalDataIntance()->getCanvasWidth(),
		KGlobalData::getGlobalDataIntance()->getCanvasHeight())); // ���� SVG ��ͼ��

	QPainter painter;
	painter.begin(&svgGenerator);

	painter.fillRect(QRect(0, 0, svgGenerator.viewBox().width(), svgGenerator.viewBox().height()), Qt::white);

	// ����ͼ���б�����ÿ��ͼ��
	if (!m_pShapeList.isEmpty())
	{
		auto it = m_pShapeList.rbegin();
		while (it != m_pShapeList.rend())
		{
			(*it)->drawSave(painter);
			it++;
		}
	}
	painter.end();
}

void KCanvas::saveToPng()
{
	QString fileName = QFileDialog::getSaveFileName(nullptr, QString::fromLocal8Bit("����ΪPNG�ļ�"), "svg.png");
	if (fileName.isEmpty())
		return;
	// ���� QImage �������ô�С
	QImage image(KGlobalData::getGlobalDataIntance()->getCanvasWidth(),
		KGlobalData::getGlobalDataIntance()->getCanvasHeight(),
		QImage::Format_ARGB32);

	QPainter painter(&image);
	painter.fillRect(image.rect(), Qt::white); // ����ɫ����

	// ����ͼ���б�����ÿ��ͼ��
	if (!m_pShapeList.isEmpty())
	{
		auto it = m_pShapeList.rbegin();
		while (it != m_pShapeList.rend())
		{
			(*it)->drawSave(painter);
			it++;
		}
	}

	painter.end();

	// ���� QImage ���ļ�
	if (!image.save(fileName)) 
	{
		qDebug() << "Failed to save PNG file:" << fileName;
	}
}

// ��ͼ�¼�����
void KCanvas::paintEvent(QPaintEvent* event)
{
	qDebug() << "paintEvent triggered";
	qDebug() << QString::fromLocal8Bit("1-��ǰѡ��ͼ�������� ") << m_isSelectedShapeList.size();
	qDebug() << QString::fromLocal8Bit("2-ɾ���б�ͼ�������� ") << m_pdeletedShapeList.size();
	qDebug() << QString::fromLocal8Bit("3-��ǰ����ͼ�������� ") << m_pShapeList.size();
	qDebug() << QString::fromLocal8Bit("--------------------------------------");
	if (m_renderer != Q_NULLPTR)
	{
		QPainter painter(this);
		m_renderer->render(&painter, this->rect());
	}

	if (!m_pShapeList.isEmpty())
	{
		auto it = m_pShapeList.rbegin();
		while (it != m_pShapeList.rend())
		{
			(*it)->drawShape(this);
			it++;
		}
	}

	if (m_pCurrentShape != Q_NULLPTR)
	{
		if (m_isDrawing) // ͼ�λ��Ʊ�־Ϊ true�����ʾ���ڻ��Ƹ�ͼ�Σ���ʱ��Ҫ�������»���
			m_pCurrentShape->drawShape(this);
	}

	if (!m_isSelectedShapeList.isEmpty())
	{
		for (auto shape : m_isSelectedShapeList)
		{
			shape->drawRectOutLine(this);
		}
	}
}

void KCanvas::mousePressEvent(QMouseEvent* event)
{
	// �������Ŵ���
	QPoint mousePos = event->pos();
	mousePos.setX(mousePos.x() / KGlobalData::getGlobalDataIntance()->getCanvasScale());
	mousePos.setY(mousePos.y() / KGlobalData::getGlobalDataIntance()->getCanvasScale());

	qDebug() << QString::fromLocal8Bit("���λ�� �� ") << mousePos;
	//��ȡ��ǰ��Ҫ���Ƶ�ͼ������
	KButtonFlag flag = KGlobalData::getGlobalDataIntance()->getButtonFlag();
	
	if (flag == KButtonFlag::NoneButtonFlag)
		return;
	
	if (event->buttons() == Qt::LeftButton)
	{
		m_isLPress = true;// ��¼�������Ѿ����
		bool ctrlPressed = event->modifiers() & Qt::ControlModifier; //���ctrl״̬
		if (flag == KButtonFlag::MouseButtonFlag)//�����ѡ��ͼ���¼�
		{
			m_pCurrentShape = getCurrentShape(mousePos);
			if (m_pCurrentShape != Q_NULLPTR)
			{
				// ��ѡ���б�Ϊ�գ����֮ǰѡ�е�ͼ���б�
				if (!ctrlPressed && m_isSelectedShapeList.size() > 0)
					m_isSelectedShapeList.clear();

				// ��ѡ
				if (ctrlPressed || m_isSelectedShapeList.isEmpty()) {
					if (!m_isSelectedShapeList.contains(m_pCurrentShape))
						m_isSelectedShapeList.append(m_pCurrentShape);
				}

				m_lastPos = mousePos;// ��ǰλ���ƶ������λ��(�����)
				m_isSelected = true;// ����ѡ�б�־
				emit shapeChosen();
				emit shapeParamChanged(m_pCurrentShape); // ����ѡ��ͼ�β���������UI
				m_TransType = getTransType(mousePos);// ��ȡ�ƶ�����
			}
			else
			{
				m_isSelected = false;
				emit canvasChosen();
				if (!ctrlPressed)
					m_isSelectedShapeList.clear();
			}
		}
		else
		{ 
			m_isSelected = false;
			m_pCurrentShape = KShapeFactory::createShape(KGlobalData::getGlobalDataIntance()->getButtonFlag());

			if (m_pCurrentShape != Q_NULLPTR)
			{
				if (flag == KButtonFlag::PenButtonFlag)
					qobject_cast<KPen*>(m_pCurrentShape)->addPos(mousePos);
				else if (flag == KButtonFlag::TextButtonFlag)
					m_pCurrentShape->setStartPoint(event->pos());
				else
					m_pCurrentShape->setStartPoint(mousePos);
			}
		}
	}
	else // �Ҽ���ʾ�˵�
	{
		m_pCurrentShape = getCurrentShape(mousePos);
		if (m_pCurrentShape != Q_NULLPTR)
			emit isSelectedShape();
	}
	update();
}

void KCanvas::mouseMoveEvent(QMouseEvent* event)
{
	QPoint mousePos = event->pos();
	mousePos.setX(mousePos.x() / KGlobalData::getGlobalDataIntance()->getCanvasScale());
	mousePos.setY(mousePos.y() / KGlobalData::getGlobalDataIntance()->getCanvasScale());

	KButtonFlag flag = KGlobalData::getGlobalDataIntance()->getButtonFlag();
	if (flag == KButtonFlag::NoneButtonFlag)
		return;

	KTransType transType = getTransType(mousePos);
	updateCusorStyle(flag, transType);//ѡ��ʱ�������ѡ����ʽ

	if (event->buttons() != Qt::LeftButton)
		return;

	if (flag != KButtonFlag::MouseButtonFlag && flag != KButtonFlag::ZoomButtonFlag)
	{
		if (m_isLPress && !m_isDrawing)
			m_isDrawing = true;
		if (m_pCurrentShape != Q_NULLPTR)
		{
			if (flag == KButtonFlag::PenButtonFlag)
				qobject_cast<KPen*>(m_pCurrentShape)->addPos(mousePos);
			else
				m_pCurrentShape->setEndPoint(mousePos);
		}
	}
	else
	{
		if (m_pCurrentShape == Q_NULLPTR)
			return;
		dragMoveShape(transType, mousePos);
		emit shapeParamChanged(m_pCurrentShape);
	}

	update();
}

void KCanvas::mouseReleaseEvent(QMouseEvent* event)
{
	KButtonFlag flag = KGlobalData::getGlobalDataIntance()->getButtonFlag();
	// ������ͼ�¼��������ѡ��ͼ���б�ȷ�����Ƶ�ǰͼ�ε�����ο�
	if (flag != KButtonFlag::MouseButtonFlag && flag != KButtonFlag::ZoomButtonFlag) {
		m_isSelectedShapeList.clear();
	}

	QPoint mousePos = event->pos();
	mousePos.setX(mousePos.x() / KGlobalData::getGlobalDataIntance()->getCanvasScale());
	mousePos.setY(mousePos.y() / KGlobalData::getGlobalDataIntance()->getCanvasScale());
	m_clickedPos = mousePos; //��¼�����λ�ã����㸴��ճ��

	if (m_isLPress) // ���������º��ͷţ����ʾ�ƶ����߻�ͼ���
	{
		if (flag != KButtonFlag::MouseButtonFlag && flag != KButtonFlag::ZoomButtonFlag)// ����ǻ�ͼ
		{
			if (m_pCurrentShape != Q_NULLPTR)
			{
				emit shapeChosen();
				if (flag == KButtonFlag::PenButtonFlag)
					qobject_cast<KPen*>(m_pCurrentShape)->addPos(mousePos);
				else if (flag == KButtonFlag::TextButtonFlag)
					qobject_cast<KText*>(m_pCurrentShape)->startEditing(event->pos(), this);
				else
					m_pCurrentShape->setEndPoint(mousePos);
				
				if (m_pCurrentShape->isValid())// �ж�ͼ�ξ����Ƿ���Ч
				{
					std::shared_ptr<KShapeParams> curparams1 = m_pCurrentShape->getCurShapeParams();
					m_pCurrentShape->setCurShapeParams(curparams1);
					m_pCurrentShape->setPrevShapeParams(); // ����ǰһ��״̬

					m_pShapeList.prepend(m_pCurrentShape);
					m_isSelectedShapeList.append(m_pCurrentShape);
				
					//���ͼ�ε�command �������
					KGlobalData::getGlobalDataIntance()->getUndoStack()->push(new KAddShapeCommand(m_pCurrentShape, 
						&m_pShapeList, &m_pdeletedShapeList));
					
					m_pCurrentShape = Q_NULLPTR;
					m_isSelected = true;
					m_isDrawing = false;
				}
				else
				{
					delete m_pCurrentShape;
					m_pCurrentShape = Q_NULLPTR;
				}
			}
		}
		else
		{
			if (m_pCurrentShape!= Q_NULLPTR)
			{
				std::shared_ptr<KShapeParams> curparams = m_pCurrentShape->getCurShapeParams();
				KGlobalData::getGlobalDataIntance()->getUndoStack()->push(new KShapeParasCommand(curparams, m_pCurrentShape));
			}
		}
		m_isLPress = false;
		m_isDrawing = false;
		m_TransType = KTransType::None;
	}

	update();  // ����update()�ᴥ����ͼ�¼�����paintEvent(QPaintEvent*)������ Qt ��ͼϵͳ�ĺ��Ļ���
}

void KCanvas::mouseDoubleClickEvent(QMouseEvent* event)
{
	QPoint mousePos = event->pos();
	mousePos.setX(mousePos.x() / KGlobalData::getGlobalDataIntance()->getCanvasScale());
	mousePos.setY(mousePos.y() / KGlobalData::getGlobalDataIntance()->getCanvasScale());

	if (m_pCurrentShape != Q_NULLPTR)
	{
		if (m_pCurrentShape->getShapeType() == KShapeType::TextShapeType)
			qobject_cast<KText*>(m_pCurrentShape)->setEditing();
	}

	update();
}

KShape* KCanvas::getCurrentShape(const QPoint &pos)
{
	for (QList<KShape*>::iterator it = m_pShapeList.begin();
		it != m_pShapeList.end(); ++it)
	{
		if ((*it)->getOutLineRect().contains(pos))
			return *it;
	}

	return Q_NULLPTR;
}

QList<KShape*>& KCanvas::getShapeList()
{
	return m_pShapeList;
}

KTransType KCanvas::getTransType(const QPoint& pos)
{
	if (!m_pCurrentShape)
		return KTransType::None;

	// ��ȡͼ�ξ���
	QRect rect = m_pCurrentShape->getOutLineRect();
	//qDebug() << QString::fromLocal8Bit("��ǰ���λ�ã� ") << pos;
	if (!rect.contains(pos))
		return KTransType::None;

	// �ж��������ƶ����ֲ���ק�ƶ�
	if (qAbs(pos.x() - rect.topLeft().x()) < 5 
			&& qAbs(pos.y() - rect.topLeft().y()) < 5)
		return KTransType::TopLeft;

	if (qAbs(rect.topRight().x() - pos.x()) < 5 
			&& qAbs(pos.y() - rect.topRight().y()) < 5)
		return KTransType::TopRight;

	if (qAbs(rect.bottomRight().x() - pos.x()) < 5 
			&& qAbs(rect.bottomRight().y() - pos.y()) < 5)
		return KTransType::BottomRight;

	if (qAbs(pos.x() - rect.bottomLeft().x()) < 5 
			&& qAbs(rect.bottomLeft().y() - pos.y()) < 5)
		return KTransType::BottomLeft;

	if (qAbs(pos.y() - rect.top()) < 5)
		return KTransType::Top;

	if (qAbs(rect.right() - pos.x()) < 5)
		return KTransType::Right;

	if (qAbs(rect.bottom() - pos.y()) < 5 )
		return KTransType::Bottom;

	if (qAbs(pos.x() - rect.left()) < 5 )
		return KTransType::Left;

	return KTransType::Contains;
}

void KCanvas::updateCusorStyle(KButtonFlag flag, KTransType transType)
{
	// ����Ѿ�ѡ��
	if (m_isSelected
		&& flag == KButtonFlag::MouseButtonFlag
		&& transType != KTransType::None)
	{
		//TODO���任ͼ��,���ò�ͬ�������ʽ,���ݵ��λ�ã����ò�ͬ�������ʽ
		if (transType == KTransType::TopLeft || transType == KTransType::BottomRight)
			setCursor(Qt::SizeFDiagCursor);
		else if (transType == KTransType::TopRight || transType == KTransType::BottomLeft)
			setCursor(Qt::SizeBDiagCursor);
		else if (transType == KTransType::Top || transType == KTransType::Bottom)
			setCursor(Qt::SizeVerCursor);
		else if (transType == KTransType::Left || transType == KTransType::Right)
			setCursor(Qt::SizeHorCursor);

		else if (transType == KTransType::Contains)
			setCursor(Qt::SizeAllCursor);
	}
	else
		unsetCursor();
}

void KCanvas::dragMoveShape(KTransType transType,const QPoint &pos)
{
	if (m_pCurrentShape == nullptr)
		return;

	/*
	���ƶ������У���Ϊ�����ƶ���ʽ��
	(1) �����ƶ�  contains
	(2) ����ĳһ���������ק�ƶ�

	*/
	switch (m_TransType)
	{
	case KTransType::None:
		return;
	case KTransType::TopLeft:
		// ��������Ͻǣ���ǰλ��Ϊ�µľ�����ʼλ��
		m_pCurrentShape->moveTopLeft(pos);
		break;
	case KTransType::Top:
		// ����������ƶ������޸���ʼλ�õ� y ����
		m_pCurrentShape->moveTop(pos);
		break;
	case KTransType::TopRight:
		m_pCurrentShape->moveTopRight(pos);
		break;
	case KTransType::Left:
		m_pCurrentShape->moveLeft(pos);
		break;
	case KTransType::Contains: // �����ƶ�
	{
		QPoint newpos = pos - m_lastPos;
		if (m_isSelectedShapeList.size() > 1)
		{
			for (auto shape : m_isSelectedShapeList)
			{
				shape->move(newpos);
			}
		}
		else
		{
			m_pCurrentShape->move(newpos);
		}
		m_lastPos = pos;
	}
	break;
	case KTransType::Right:
		m_pCurrentShape->moveRight(pos);
		break;
	case KTransType::BottomLeft:
		m_pCurrentShape->moveBottomLeft(pos);
		break;
	case KTransType::Bottom:
		m_pCurrentShape->moveBottom(pos);
		break;
	case KTransType::BottomRight:
		m_pCurrentShape->moveBottomRight(pos);
		break;
	default:
		break;
	}
}

int KCanvas::findShapeIndex(KShape* shapeToFind) const
{
	int index = -1; 

	QList<KShape*>::const_iterator it;
	for (it = m_pShapeList.begin(); it != m_pShapeList.end(); ++it) 
	{
		if (*it == shapeToFind) 
		{
			index = std::distance(m_pShapeList.begin(), it);  //index
			break;  
		}
	}

	return index;
}