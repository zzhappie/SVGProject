#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include "ktoolbar.h"
#include "kfilemenubar.h"
#include "kshapeparascommand.h"
#include "kcanvasparascommand.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/mainwindow/icons/svg.png"));
    setWindowTitle("SVG Editor Window");

    initMainWindow();
    initConnection();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initMainWindow()
{
    // 不用动态创建，已经在ui文件中提升了
    // ui->m_pToolBar = new KToolBar(this);
    m_pCanvasWidgetVLayout = new QVBoxLayout(ui->m_pCanvasWidget);
    m_pKSvgMainWin = new KSvgMainWindow(ui->m_pCanvasWidget);
    m_pCanvasWidgetVLayout->addWidget(m_pKSvgMainWin);

    m_pCanvasParamsBarWidgetVLayout = new QVBoxLayout(ui->m_pCanvasParamsWidget);
    m_pCanvasParamsBar = new KCanvasParamsBar(QStringLiteral("画布参数"), ui->m_pCanvasParamsWidget);
    m_pCanvasParamsBarWidgetVLayout->addWidget(m_pCanvasParamsBar);

    m_pShapeParamsBarWidgetVLayout = new QVBoxLayout(ui->m_pShapeParamsWidget);
    m_pShapeParamsBar = new KShapeParamsBar(QStringLiteral("图形参数"), ui->m_pShapeParamsWidget);
    m_pShapeParamsBarWidgetVLayout->addWidget(m_pShapeParamsBar);

    initFileMenu();
    ui->m_pShapeParamsWidget->hide();
}

void MainWindow::initConnection()
{
    connect(m_pKSvgMainWin, &KSvgMainWindow::scaleChanged, this, [this](qreal value)
        {
            m_pCanvasParamsBar->m_pScaleBox->m_pParamEdit->setText(QString::number(value * 100));
        });

    (void)connect(m_pCanvasParamsBar->m_pWidthBox->m_pParamEdit, &QLineEdit::editingFinished, this, &MainWindow::validateCanvasParams);
    (void)connect(m_pCanvasParamsBar->m_pHeightBox->m_pParamEdit, &QLineEdit::editingFinished, this, &MainWindow::validateCanvasParams);
    (void)connect(m_pCanvasParamsBar->m_pScaleBox->m_pParamEdit, &QLineEdit::editingFinished, this, &MainWindow::validateCanvasParams);
    (void)connect(m_pCanvasParamsBar->m_pColorBox, &KColorBox::pickedColor, this, &MainWindow::validateCanvasParams);

    (void)connect(m_pShapeParamsBar->m_pBorderWidthBox->m_pParamEdit, &QLineEdit::editingFinished, this, &MainWindow::validateShapeParams);
    (void)connect(m_pShapeParamsBar->m_pBorderStyleBox->m_pBorderStyleComboBox, qOverload<int>(&QComboBox::currentIndexChanged), this, &MainWindow::switchPenStyle);
    (void)connect(m_pShapeParamsBar->m_pBorderColorBox, &KColorBox::pickedColor, this, &MainWindow::validateShapeParams);
    (void)connect(m_pShapeParamsBar->m_pFillColorBox, &KColorBox::pickedColor, this, &MainWindow::validateShapeParams);

    (void)connect(m_pKSvgMainWin->m_pCanvas, &KCanvas::shapeParamChanged, this, &MainWindow::updateSelectedShapeParamsToParamsBar);
    (void)connect(m_pKSvgMainWin->m_pCanvas, &KCanvas::canvasParamsChanged, this, &MainWindow::updateCanvasParamsToParamsBar);

    (void)connect(m_pKSvgMainWin->m_pCanvas, &KCanvas::shapeChosen, this, &MainWindow::shiftToParamsBar);
    (void)connect(m_pKSvgMainWin->m_pCanvas, &KCanvas::canvasChosen, this, &MainWindow::shiftToCanvasBar);
    (void)connect(m_pKSvgMainWin, &KSvgMainWindow::canvasChosen, this, &MainWindow::shiftToCanvasBar);

    (void)connect(ui->m_creatFileAct, &QAction::triggered, m_pKSvgMainWin->m_pCanvas, &KCanvas::createCanvas);
    (void)connect(ui->m_openSVGAct, &QAction::triggered, m_pKSvgMainWin->m_pCanvas, &KCanvas::loadSvg);
    (void)connect(ui->m_saveAct, &QAction::triggered, m_pKSvgMainWin->m_pCanvas, &KCanvas::saveToSvg);
    (void)connect(ui->m_savePNGAct, &QAction::triggered, m_pKSvgMainWin->m_pCanvas, &KCanvas::saveToPng);
}

void MainWindow::initFileMenu()
{
    ui->m_creatFileAct->setShortcuts(QKeySequence::New);
    ui->m_creatFileAct->setStatusTip(QString::fromLocal8Bit("创建新的画布"));

    ui->m_openSVGAct->setShortcuts(QKeySequence::Open);
    ui->m_openSVGAct->setStatusTip(tr("打开SVG"));

    ui->m_saveAct->setShortcuts(QKeySequence::Save);
    ui->m_saveAct->setStatusTip(QString::fromLocal8Bit("保存当前文件"));

    ui->m_savePNGAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_E));
    ui->m_savePNGAct->setStatusTip(QString::fromLocal8Bit("当前图形导出"));
}

void MainWindow::shiftToParamsBar()
{
    ui->m_pCanvasParamsWidget->hide();
    ui->m_pShapeParamsWidget->show();
}

void MainWindow::shiftToCanvasBar() 
{
    ui->m_pCanvasParamsWidget->show();
    ui->m_pShapeParamsWidget->hide();
}

void MainWindow::validateCanvasParams()
{
    int width = m_pCanvasParamsBar->m_pWidthBox->m_pParamEdit->text().toInt();
    int height = m_pCanvasParamsBar->m_pHeightBox->m_pParamEdit->text().toInt();
    qreal scale = m_pCanvasParamsBar->m_pScaleBox->m_pParamEdit->text().toDouble() / 100;
    QString canvasC = KGlobalData::getGlobalDataIntance()->getCanvasColor();

    KGlobalData::getGlobalDataIntance()->setCanvasWidth(width);
    KGlobalData::getGlobalDataIntance()->setCanvasHeight(height);
    KGlobalData::getGlobalDataIntance()->setCanvaScale(scale);

    m_pKSvgMainWin->m_pCanvas->resize(width, height);
    m_pKSvgMainWin->m_pCanvas->resize(width * scale, height * scale);
    m_pKSvgMainWin->m_pCanvas->setStyleSheet(QString("background-color:#%1").arg(canvasC));

    int preW = KGlobalData::getGlobalDataIntance()->getPrevCanvasWidth();
    int preH = KGlobalData::getGlobalDataIntance()->getPrevCanvasHeight();
    QString preC = KGlobalData::getGlobalDataIntance()->getPrevCanvasColor();
    if (preW == width && preH == height && preC == canvasC)
        return;
    // 画布操作入栈
    KCanvasParams* canvasParams = new KCanvasParams(width, height, KGlobalData::getGlobalDataIntance()->getCanvasColor(),KGlobalData::getGlobalDataIntance()->getPrevCanvasWidth(),
        KGlobalData::getGlobalDataIntance()->getPrevCanvasHeight(), KGlobalData::getGlobalDataIntance()->getPrevCanvasColor(), KGlobalData::getGlobalDataIntance()->getCanvasScale());
    KGlobalData::getGlobalDataIntance()->getUndoStack()->push(new KCanvasParasCommand(canvasParams));
}

void MainWindow::validateShapeParams()
{
    Qt::PenStyle penStyle = KGlobalData::getGlobalDataIntance()->getPenStyle();
    qint32 borderWidth = m_pShapeParamsBar->m_pBorderWidthBox->m_pParamEdit->text().toInt();
    QColor borderColor = KGlobalData::getGlobalDataIntance()->getBoderColor();
    QColor fillColor = KGlobalData::getGlobalDataIntance()->getFillColor();

    KGlobalData::getGlobalDataIntance()->setBorderWidth(borderWidth);
    KGlobalData::getGlobalDataIntance()->setBoderColor(borderColor);
    KGlobalData::getGlobalDataIntance()->setFillColor(fillColor);
    KGlobalData::getGlobalDataIntance()->setPenStyle(penStyle);

    // 选中当前形状也可改变样式
    if (m_pKSvgMainWin->m_pCanvas->m_pCurrentShape != Q_NULLPTR)
    {
        m_pKSvgMainWin->m_pCanvas->m_pCurrentShape->setBorderColor(borderColor);
        m_pKSvgMainWin->m_pCanvas->m_pCurrentShape->setBorderWidth(borderWidth);
        m_pKSvgMainWin->m_pCanvas->m_pCurrentShape->setFillColor(fillColor);
        m_pKSvgMainWin->m_pCanvas->m_pCurrentShape->setPenStyle(penStyle);
        m_pKSvgMainWin->m_pCanvas->update();
        std::shared_ptr<KShapeParams> curParams = m_pKSvgMainWin->m_pCanvas->m_pCurrentShape->getCurShapeParams();
        std::shared_ptr<KShapeParams> prevParams = m_pKSvgMainWin->m_pCanvas->m_pCurrentShape->getPrevShapeParams();
        if (curParams == prevParams)
            return;
        KGlobalData::getGlobalDataIntance()->getUndoStack()->push(new KShapeParasCommand(curParams, m_pKSvgMainWin->m_pCanvas->m_pCurrentShape));
    }
}

void MainWindow::updateSelectedShapeParamsToParamsBar(KShape* shape)
{
    std::shared_ptr<KShapeParams> curShapeParams = shape->getCurShapeParams();

    KGlobalData::getGlobalDataIntance()->setBoderColor(curShapeParams->m_borderColor);
    KGlobalData::getGlobalDataIntance()->setFillColor(curShapeParams->m_fillColor);
    KGlobalData::getGlobalDataIntance()->setBorderWidth(curShapeParams->m_borderWidth);
    KGlobalData::getGlobalDataIntance()->setPenStyle(curShapeParams->m_penStyle);

    m_pShapeParamsBar->m_pShapeWidthBox->m_pParamEdit->setText(QString::number(curShapeParams->m_width));
    m_pShapeParamsBar->m_pShapeHeightBox->m_pParamEdit->setText(QString::number(curShapeParams->m_height));
    m_pShapeParamsBar->m_pBorderWidthBox->m_pParamEdit->setText(QString::number(curShapeParams->m_borderWidth));

    QString borderColorStr = curShapeParams->m_borderColor.name();
    m_pShapeParamsBar->m_pBorderColorBox->m_pColorBtn->setStyleSheet(
        QString("border-width: 0px; background-color:%1 ; border-style:outset;margin:5px").arg(borderColorStr));
    
    QString fillColorStr = curShapeParams->m_fillColor.name();
    m_pShapeParamsBar->m_pFillColorBox->m_pColorBtn->setStyleSheet(
        QString("border-width: 0px; background-color:%1 ; border-style:outset;margin:5px").arg(fillColorStr));
}

void MainWindow::updateCanvasParamsToParamsBar()
{
    qint32 width = KGlobalData::getGlobalDataIntance()->getCanvasWidth();
    qint32 height = KGlobalData::getGlobalDataIntance()->getCanvasHeight();
    QString str = KGlobalData::getGlobalDataIntance()->getCanvasColor();
    qreal scale = KGlobalData::getGlobalDataIntance()->getCanvasScale();
    m_pKSvgMainWin->m_pCanvas->resize(width * scale, height * scale);
    m_pCanvasParamsBar->m_pWidthBox->m_pParamEdit->setText(QString::number(width));
    m_pCanvasParamsBar->m_pHeightBox->m_pParamEdit->setText(QString::number(height));
    m_pCanvasParamsBar->m_pColorBox->m_pColorBtn->setStyleSheet(
        QString("border-width: 0px; background-color:#%1; border-style:outset;margin:5px").arg(str));

    m_pKSvgMainWin->m_pCanvas->setStyleSheet(QString("background-color:#%1").arg(str));
}

void MainWindow::switchPenStyle(const int index)
{
    switch (index)
    {
    case 0:
        KGlobalData::getGlobalDataIntance()->setPenStyle(Qt::SolidLine);
        break;
    case 1:
        KGlobalData::getGlobalDataIntance()->setPenStyle(Qt::DotLine);
        break;
    case 2:
        KGlobalData::getGlobalDataIntance()->setPenStyle(Qt::DashLine);
        break;
    case 3:
        KGlobalData::getGlobalDataIntance()->setPenStyle(Qt::DashDotLine);
        break;
    case 4:
        KGlobalData::getGlobalDataIntance()->setPenStyle(Qt::DashDotDotLine);
        break;
    }
    validateShapeParams();
}

