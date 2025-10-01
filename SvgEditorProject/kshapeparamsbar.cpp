#include "kshapeparamsbar.h"

KShapeParamsBar::KShapeParamsBar(const QString& title, QWidget* parent)
	: KParamsBar(title, parent)
	, m_pBorderWidthBox(Q_NULLPTR)
	, m_pBorderStyleBox(Q_NULLPTR)
	, m_pBorderColorBox(Q_NULLPTR)
	, m_pFillColorBox(Q_NULLPTR)

{
	m_pBorderWidthBox = new KValueBox(QStringLiteral("边框宽度"), KGlobalData::getGlobalDataIntance()->getBorderWidth(), this);
	m_pBorderStyleBox = new KComboBox(QStringLiteral("边框样式"), this);
	m_pBorderColorBox = new KColorBox(QStringLiteral("边框颜色"), KGlobalData::getGlobalDataIntance()->getBoderColor().name().mid(1), KColorFlag::ShapeBorderColorFlag, this);
	m_pFillColorBox = new KColorBox(QStringLiteral("填充颜色"), KGlobalData::getGlobalDataIntance()->getFillColor().name().mid(1), KColorFlag::ShapeFillColorFlag, this);
	m_pShapeWidthBox = new KValueBox(QStringLiteral("图形宽度"), 0, this);
	m_pShapeHeightBox = new KValueBox(QStringLiteral("图形高度"), 0, this);

	// 给边框线条样式初始化
	QIcon icon0(":/paramsbar/icons/borderStyle/solidline.png");
	QIcon icon1(":/paramsbar/icons/borderStyle/dotline.png");
	QIcon icon2(":/paramsbar/icons/borderStyle/dashline.png");
	QIcon icon3(":/paramsbar/icons/borderStyle/dashdotline.png");
	QIcon icon4(":/paramsbar/icons/borderStyle/dashdotdotline.png");
	m_pBorderStyleBox->addItemWithIcon(icon0);
	m_pBorderStyleBox->addItemWithIcon(icon1);
	m_pBorderStyleBox->addItemWithIcon(icon2);
	m_pBorderStyleBox->addItemWithIcon(icon3);
	m_pBorderStyleBox->addItemWithIcon(icon4);

	// 添加到网格布局
	m_pGridLayout->addWidget(m_pShapeWidthBox, 1, 0);
	m_pGridLayout->addWidget(m_pShapeHeightBox, 1, 1);
	m_pGridLayout->addWidget(m_pBorderWidthBox, 2, 0);
	m_pGridLayout->addWidget(m_pBorderStyleBox, 2, 1);
	m_pGridLayout->addWidget(m_pBorderColorBox, 3, 0);
	m_pGridLayout->addWidget(m_pFillColorBox, 3, 1);
	m_pGridLayout->setSpacing(10); // 间距为 10 像素
}

KShapeParamsBar::~KShapeParamsBar()
{
}

