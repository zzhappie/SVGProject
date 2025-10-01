#ifndef __K_SVG_MAINWINDOW_H_
#define __K_SVG_MAINWINDOW_H_

#include <QScrollArea>
#include "kglobaldata.h"
#include "kcanvas.h"

// -------------------------------------------------------
// ksvgmainwindow.h
// �����ߣ� �ӻ���
// ����ʱ�䣺 2025/4/19
// ���������� svg�༭����
// Copyright 2025 Kingsoft
// --------------------------------------------------------

class KCanvasMenu;

class KSvgMainWindow : public QScrollArea
{
	Q_OBJECT
	friend class MainWindow;

public:
	KSvgMainWindow(QWidget *parent);
	~KSvgMainWindow();

	void setCursorStyle(KButtonFlag buttonFlag);

	void enterEvent(QEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;

signals:
	void scaleChanged(qreal value);
	void canvasChosen();

private slots:
	//ȫѡ
	void selectAllShape();

	// ���ơ����С���д��ճ��
	void cutCurrentShape();
	void copyCurrentShape();
	void pasteCurrentShape();
	void copyAndPasteCurrentShape();

	// ɾ��
	void deleteCurrentShape();

	// ͼ�����
	void upLayer();
	void downLayer();
	void upFrontLayer();
	void downBackLayer();

	// ͼ�εĳ���ǰ������
	void shapeUndo();
	void shapeRedo();
private:
	void initCanvasMenuConnection();
	void initPenCursor();
	KCanvas *m_pCanvas;
	KCanvasMenu* m_canvasMenu;
	QCursor penCursor; // pen�������ʽ
};
#endif