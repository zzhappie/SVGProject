#ifndef __K_GLOBAL_DATA_H__
#define __K_GLOBAL_DATA_H__

#include <QObject>
#include <memory>
#include <QColor>
#include <QUndoStack>
#include <QNetworkAccessManager>
#include <QMap>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

// -------------------------------------------------------
// kglobaldata.h
// 创建者： 钟欢欢
// 创建时间： 2025/4/12
// 功能描述： 存放、读写全局数据
// Copyright 2025 Kingsoft
// --------------------------------------------------------

// 侧边栏按钮标识
enum class KButtonFlag
{
	NoneButtonFlag = 0,
	MouseButtonFlag,
	PenButtonFlag,
	LineButtonFlag,
	RectButtonFlag,
	CircleButtonFlag,
	PentButtonFlag,
	HexaButtonFlag,
	StarButtonFlag,
	TextButtonFlag,
	ZoomButtonFlag,
	HeartButtonFlag,
	BubbleButtonFlag
};

// 颜色标志
enum class KColorFlag 
{
	NoneColorFlag = 0,
	CanvasColorFlag,
	ShapeBorderColorFlag,
	ShapeFillColorFlag,
};

// 绘图类型
enum class KShapeType
{
	None = 0,
	PenShapeType,
	LineShapeType,
	CircleShapeType,
	RectShapeType,
	PentShapeType,
	HexaShapeType,
	StarShapeType,
	TextShapeType,
	HeartShapeType,
	BubbleShapeType
};

// 移动类型
enum class KTransType
{
	None = 0,
	TopLeft,
	Top,
	TopRight,
	Left,
	Contains,// 全部 
	Right,
	BottomLeft,
	Bottom,
	BottomRight
};

// 图形参数结构体
struct KShapeParams
{
	QPoint m_startPoint; // 起始坐标
	QPoint m_endPoint; // 结束坐标
	int m_width;
	int m_height;
	int m_borderWidth; //边框宽度
	QColor m_borderColor; //边框颜色
	Qt::PenStyle m_penStyle; // 画笔样式
	QColor m_fillColor; //填充颜色

	KShapeParams(): 
		m_startPoint(0, 0),
		m_endPoint(0, 0),
		m_width(0),
		m_height(0),
		m_borderWidth(2),
		m_borderColor(Qt::black),
		m_penStyle(Qt::SolidLine),
		m_fillColor(Qt::white) {}

	// 检查两个对象是否相等
	bool operator==(const KShapeParams& other) const
	{
		return m_startPoint == other.m_startPoint &&
			m_endPoint == other.m_endPoint &&
			m_width == other.m_width &&
			m_height == other.m_height &&
			m_borderWidth == other.m_borderWidth &&
			m_borderColor == other.m_borderColor &&
			m_penStyle == other.m_penStyle &&
			m_fillColor == other.m_fillColor;
	}
};

// 画布参数结构体
struct KCanvasParams
{
	int m_canvasWidth; //画布宽度
	int m_canvasHeight; //画布高度
	QString m_canvasColor; // 画布颜色
	int m_prevCanvasWidth; // 上一次画布的宽度
	int m_prevCanvasHeight; // 上一次画布的高度
	QString m_prevCanvasColor; // 上一次画布的颜色
	qreal m_scale; // 画布缩放比例

	KCanvasParams() :
		m_canvasWidth(1200),
		m_canvasHeight(900),
		m_canvasColor("FFFFFF"),
		m_prevCanvasColor("FFFFFF"),
		m_prevCanvasWidth(1200),
		m_prevCanvasHeight(900),
		m_scale(1.0) {}
	KCanvasParams(int canvasWidth, int canvasHeight, QString canvasColor, 
		int prevCanvasWidth, int prevCanvasHeight, QString prevCanvasColor, qreal scale) {
		m_canvasWidth = canvasWidth;
		m_canvasHeight = canvasHeight;
		m_canvasColor = canvasColor;
		m_prevCanvasColor = prevCanvasColor;
		m_prevCanvasWidth = prevCanvasWidth;
		m_prevCanvasHeight = prevCanvasHeight;
		m_scale = scale;
	}
};

class KGlobalData : public QObject
{
	Q_OBJECT
public:
	explicit KGlobalData(QObject* parent = Q_NULLPTR);
	~KGlobalData();

	static std::shared_ptr<KGlobalData> getGlobalDataIntance();

	void setButtonFlag(KButtonFlag buttonflag);
	KButtonFlag getButtonFlag();

	void setColorFlag(KColorFlag colorflag);
	KColorFlag getColorFlag();

	// 图形参数
	void setBorderWidth(const int value);
	int getBorderWidth() const;

	void setBoderColor(const QColor color);
	QColor getBoderColor();

	Qt::PenStyle getPenStyle() const;
	void setPenStyle(const Qt::PenStyle pen_style);

	void setFillColor(const QColor color);
	QColor getFillColor();

	// 画布参数
	int getCanvasWidth() const;
	void setCanvasWidth(const int width);

	int getCanvasHeight() const;
	void setCanvasHeight(const int height);

	QString getCanvasColor();
	void setCanvasColor(const QString& colorStr);

	int getPrevCanvasWidth() const;
	void setPrevCanvasWidth(const int width);

	int getPrevCanvasHeight() const;
	void setPrevCanvasHeight(const int height);

	QString getPrevCanvasColor();
	void setPrevCanvasColor(const QString& colorStr);

	qreal getCanvasScale() const;
	void setCanvaScale(qreal scale);

	QUndoStack* getUndoStack();

	void loadButtonTips(); // 加载按钮提示信息
	QPair<QString, QString> getButtonTip(KButtonFlag flag) const; // 获取指定按钮的提示信息

private slots:
	void onButtonTipsDownloaded(QNetworkReply* reply); // 处理下载完成的槽函数

private:
	KGlobalData(const KGlobalData& other) = delete;
	KGlobalData(const KGlobalData&& other) = delete;
	void operator=(const KGlobalData) = delete;

	static std::shared_ptr<KGlobalData> s_pInstance;

	KButtonFlag m_buttonFlag;
	KColorFlag m_colorFlag;

	KShapeParams* m_pShapeParams;
	KCanvasParams* m_pCanvasParams;

	// 全局的栈，用来存储uodo、redo命令
	QUndoStack m_undoStack;

	// 在线配置
	QNetworkAccessManager* m_pNetworkManager;
	QMap<KButtonFlag, QPair<QString, QString>> m_buttonTips; // 存储按钮提示信息
};
#endif

