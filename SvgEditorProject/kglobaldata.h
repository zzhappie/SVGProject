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
// �����ߣ� �ӻ���
// ����ʱ�䣺 2025/4/12
// ���������� ��š���дȫ������
// Copyright 2025 Kingsoft
// --------------------------------------------------------

// �������ť��ʶ
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

// ��ɫ��־
enum class KColorFlag 
{
	NoneColorFlag = 0,
	CanvasColorFlag,
	ShapeBorderColorFlag,
	ShapeFillColorFlag,
};

// ��ͼ����
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

// �ƶ�����
enum class KTransType
{
	None = 0,
	TopLeft,
	Top,
	TopRight,
	Left,
	Contains,// ȫ�� 
	Right,
	BottomLeft,
	Bottom,
	BottomRight
};

// ͼ�β����ṹ��
struct KShapeParams
{
	QPoint m_startPoint; // ��ʼ����
	QPoint m_endPoint; // ��������
	int m_width;
	int m_height;
	int m_borderWidth; //�߿���
	QColor m_borderColor; //�߿���ɫ
	Qt::PenStyle m_penStyle; // ������ʽ
	QColor m_fillColor; //�����ɫ

	KShapeParams(): 
		m_startPoint(0, 0),
		m_endPoint(0, 0),
		m_width(0),
		m_height(0),
		m_borderWidth(2),
		m_borderColor(Qt::black),
		m_penStyle(Qt::SolidLine),
		m_fillColor(Qt::white) {}

	// ������������Ƿ����
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

// ���������ṹ��
struct KCanvasParams
{
	int m_canvasWidth; //�������
	int m_canvasHeight; //�����߶�
	QString m_canvasColor; // ������ɫ
	int m_prevCanvasWidth; // ��һ�λ����Ŀ��
	int m_prevCanvasHeight; // ��һ�λ����ĸ߶�
	QString m_prevCanvasColor; // ��һ�λ�������ɫ
	qreal m_scale; // �������ű���

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

	// ͼ�β���
	void setBorderWidth(const int value);
	int getBorderWidth() const;

	void setBoderColor(const QColor color);
	QColor getBoderColor();

	Qt::PenStyle getPenStyle() const;
	void setPenStyle(const Qt::PenStyle pen_style);

	void setFillColor(const QColor color);
	QColor getFillColor();

	// ��������
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

	void loadButtonTips(); // ���ذ�ť��ʾ��Ϣ
	QPair<QString, QString> getButtonTip(KButtonFlag flag) const; // ��ȡָ����ť����ʾ��Ϣ

private slots:
	void onButtonTipsDownloaded(QNetworkReply* reply); // ����������ɵĲۺ���

private:
	KGlobalData(const KGlobalData& other) = delete;
	KGlobalData(const KGlobalData&& other) = delete;
	void operator=(const KGlobalData) = delete;

	static std::shared_ptr<KGlobalData> s_pInstance;

	KButtonFlag m_buttonFlag;
	KColorFlag m_colorFlag;

	KShapeParams* m_pShapeParams;
	KCanvasParams* m_pCanvasParams;

	// ȫ�ֵ�ջ�������洢uodo��redo����
	QUndoStack m_undoStack;

	// ��������
	QNetworkAccessManager* m_pNetworkManager;
	QMap<KButtonFlag, QPair<QString, QString>> m_buttonTips; // �洢��ť��ʾ��Ϣ
};
#endif

