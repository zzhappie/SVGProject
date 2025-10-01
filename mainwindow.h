#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QMainWindow>
#include <QVBoxLayout>

#include "kglobaldata.h"
#include "kshape.h"
#include "ksvgmainwindow.h"
#include "kcanvasparamsbar.h"
#include "kshapeparamsbar.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initMainWindow();
    void initConnection();
    void initFileMenu();

    void shiftToParamsBar();
    void shiftToCanvasBar();

private slots:
    void validateCanvasParams();
    void validateShapeParams();
    void updateSelectedShapeParamsToParamsBar(KShape* shape);
    void updateCanvasParamsToParamsBar();

private:
    void switchPenStyle(int index);
    Ui::MainWindow *ui;
    QVBoxLayout* m_pCanvasWidgetVLayout;
    QVBoxLayout* m_pCanvasParamsBarWidgetVLayout;
    QVBoxLayout* m_pShapeParamsBarWidgetVLayout;
    QVBoxLayout* m_pFileMenuWidgetVLayout;

    KSvgMainWindow* m_pKSvgMainWin;
    KCanvasParamsBar* m_pCanvasParamsBar;
    KShapeParamsBar* m_pShapeParamsBar;
};
#endif // MAINWINDOW_H
