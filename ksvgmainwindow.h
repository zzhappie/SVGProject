#ifndef __K_SVG_MAINWINDOW_H_
#define __K_SVG_MAINWINDOW_H_

#include <QScrollArea>
#include "kglobaldata.h"
#include "kcanvas.h"

// -------------------------------------------------------
// ksvgmainwindow.h
// 创建者： 钟欢欢
// 创建时间： 2025/4/19
// 功能描述： svg编辑窗口
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
	//全选
	void selectAllShape();

	// 复制、剪切、复写、粘贴
	void cutCurrentShape();
	void copyCurrentShape();
	void pasteCurrentShape();
	void copyAndPasteCurrentShape();

	// 删除
	void deleteCurrentShape();

	// 图层操作
	void upLayer();
	void downLayer();
	void upFrontLayer();
	void downBackLayer();

	// 图形的撤退前进操作
	void shapeUndo();
	void shapeRedo();
private:
	void initCanvasMenuConnection();
	void initPenCursor();
	KCanvas *m_pCanvas;
	KCanvasMenu* m_canvasMenu;
	QCursor penCursor; // pen的鼠标样式
};
#endif