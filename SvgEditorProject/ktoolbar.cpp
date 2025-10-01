#include "ktoolbar.h"
#include "kglobaldata.h"

KToolBar::KToolBar(QWidget *parent)
	: QWidget(parent)
	, m_pVLayout(nullptr)
	, m_pBtnGroup(nullptr)
	, m_pMouseBtn(nullptr)
	, m_pPenBtn(nullptr)
	, m_pLineBtn(nullptr)
	, m_pRectBtn(nullptr)
	, m_pCircleBtn(nullptr)
	, m_pHeartBtn(nullptr)
	, m_pBubbleBtn(nullptr)
	, m_pTextBtn(nullptr)
	, m_pZoomBtn(nullptr)
{
	setMaximumWidth(60);

	//垂直布局对象
	m_pVLayout = new QVBoxLayout(this);
	m_pVLayout->setAlignment(Qt::AlignVCenter | Qt::AlignTop);
	m_pVLayout->setSpacing(30);

	m_pBtnGroup = new QButtonGroup(this);
	m_pBtnGroup->setExclusive(true);// 设置互斥，只能有一个按钮处于 checked 状态

	// 创建 自定义按钮
	m_pMouseBtn = new KToolButton(KButtonFlag::MouseButtonFlag, this);
	m_pPenBtn = new KToolButton(KButtonFlag::PenButtonFlag, this);
	m_pLineBtn = new KToolButton(KButtonFlag::LineButtonFlag, this);
	m_pRectBtn = new KToolButton(KButtonFlag::RectButtonFlag, this);
	m_pCircleBtn = new KToolButton(KButtonFlag::CircleButtonFlag, this);
	m_pPentBtn = new KToolButton(KButtonFlag::PentButtonFlag, this);
	m_pHexaBtn = new KToolButton(KButtonFlag::HexaButtonFlag, this);
	m_pStarBtn = new KToolButton(KButtonFlag::StarButtonFlag, this);
	m_pHeartBtn = new KToolButton(KButtonFlag::HeartButtonFlag, this);
	m_pBubbleBtn = new KToolButton(KButtonFlag::BubbleButtonFlag, this);
	m_pTextBtn = new KToolButton(KButtonFlag::TextButtonFlag, this);
	m_pZoomBtn = new KToolButton(KButtonFlag::ZoomButtonFlag, this);

	// 将按钮添加到 按钮组中
	m_pBtnGroup->addButton(m_pMouseBtn);
	m_pBtnGroup->addButton(m_pPenBtn);
	m_pBtnGroup->addButton(m_pLineBtn);
	m_pBtnGroup->addButton(m_pRectBtn);
	m_pBtnGroup->addButton(m_pCircleBtn);
	m_pBtnGroup->addButton(m_pPentBtn);
	m_pBtnGroup->addButton(m_pHexaBtn);
	m_pBtnGroup->addButton(m_pStarBtn);
	m_pBtnGroup->addButton(m_pHeartBtn);
	m_pBtnGroup->addButton(m_pBubbleBtn);
	m_pBtnGroup->addButton(m_pTextBtn);
	m_pBtnGroup->addButton(m_pZoomBtn);

	// 将自定义按钮添加到布局器中
	m_pVLayout->addWidget(m_pMouseBtn);
	m_pVLayout->addWidget(m_pPenBtn);
	m_pVLayout->addWidget(m_pLineBtn);
	m_pVLayout->addWidget(m_pRectBtn);
	m_pVLayout->addWidget(m_pCircleBtn);
	m_pVLayout->addWidget(m_pPentBtn);
	m_pVLayout->addWidget(m_pHexaBtn);
	m_pVLayout->addWidget(m_pStarBtn);
	m_pVLayout->addWidget(m_pHeartBtn);
	m_pVLayout->addWidget(m_pBubbleBtn);
	m_pVLayout->addWidget(m_pTextBtn);
	m_pVLayout->addWidget(m_pZoomBtn);
	
	// 将布局器添加到 qwidget 中
	setLayout(m_pVLayout);
}

KToolBar::~KToolBar()
{
}
