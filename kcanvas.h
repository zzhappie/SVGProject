#ifndef __K_CANVAS_H__
#define __K_CANVAS_H__

#include <QWidget>
#include <QSvgRenderer>
#include <QUndoStack>

#include "kshape.h"
#include "kglobaldata.h"
#include "kclipboard.h"

// -------------------------------------------------------
// kcanvas.h
// �����ߣ� �ӻ���
// ����ʱ�䣺 2025/4/16
// ���������� ����
// Copyright 2025 Kingsoft
// --------------------------------------------------------

class KCanvas : public QWidget
{
	Q_OBJECT
	friend class MainWindow;
	friend class KSvgMainWindow;
public:
	KCanvas(QWidget *parent = Q_NULLPTR);
	~KCanvas();

	virtual void paintEvent(QPaintEvent* event) override;
	virtual void mousePressEvent(QMouseEvent* event) override;
	virtual void mouseMoveEvent(QMouseEvent* event) override;
	virtual void mouseReleaseEvent(QMouseEvent* event) override;
	virtual void mouseDoubleClickEvent(QMouseEvent* event) override; // �༭�ı���ʹ��

	KShape* getCurrentShape(const QPoint &pos);// ��ȡ��ǰλ��ͼ��
	QList <KShape*>& getShapeList();
	KTransType getTransType(const QPoint &pos); // ��ȡ�ƶ�����
	void updateCusorStyle(KButtonFlag flag, KTransType transType);
	void dragMoveShape(KTransType transType, const QPoint& pos);

	// �ļ��������½������롢����
	void createCanvas();
	void loadSvg();
	void saveToSvg();
	void saveToPng();

signals:
	void shapeParamChanged(KShape* shape);
	void canvasParamsChanged();
	void isSelectedShape();
	void shapeChosen();
	void canvasChosen();

private:
	int findShapeIndex(KShape* shapeToFind) const;
	QSvgRenderer* m_renderer; // ����svg��Ⱦ

	KShape* m_pCurrentShape;
	QList <KShape*> m_pShapeList;// �洢��ǰ�����е�ͼ��
	QList <KShape*> m_isSelectedShapeList; //��ѡ�е�ͼ�ε���������һ��һ��ѡ��ͼ��
	QList <KShape*> m_pdeletedShapeList; // ���ɾ��ͼ�ε�����������������λ���ͷ��ڴ�
	QPoint m_lastPos;// ��¼ǰһ�ε�λ��
	KTransType m_TransType;// ��¼�ƶ�����
	
	bool m_isLPress;// ���������
	bool m_isDrawing;// �Ƿ��ͼ
	bool m_isSelected;// �Ƿ�Ϊѡ��
	bool m_isRender; // �Ƿ����svg

	KShapeClipboard* m_pClipBoard; // ���а�
	QPoint m_clickedPos; //��ǰ���ѡ��λ�ã�������ճ������ͼ��ָ��λ��ʹ��
};
#endif