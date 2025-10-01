#include "kglobaldata.h"

#include <mutex>

KGlobalData::KGlobalData(QObject* parent)
    : QObject(parent)
    , m_buttonFlag(KButtonFlag::NoneButtonFlag)
    , m_colorFlag(KColorFlag::NoneColorFlag)
    , m_pShapeParams(new KShapeParams)
    , m_pCanvasParams(new KCanvasParams)
    , m_pNetworkManager(new QNetworkAccessManager(this))

{
    (void)connect(m_pNetworkManager, &QNetworkAccessManager::finished, this, &KGlobalData::onButtonTipsDownloaded);
}

std::shared_ptr<KGlobalData> KGlobalData::s_pInstance;

KGlobalData::~KGlobalData()
{
}

std::shared_ptr<KGlobalData> KGlobalData::getGlobalDataIntance()
{
    static std::once_flag s_flag;
    std::call_once(s_flag, [&]() {
        s_pInstance = std::shared_ptr<KGlobalData>(new KGlobalData);
        });

    return s_pInstance;
}

void KGlobalData::setButtonFlag(KButtonFlag buttonFlag)
{
    this->m_buttonFlag = buttonFlag;
}

KButtonFlag KGlobalData::getButtonFlag()
{
    return m_buttonFlag;
}

void KGlobalData::setColorFlag(KColorFlag colorflag)
{
    this->m_colorFlag = colorflag;
}

KColorFlag KGlobalData::getColorFlag()
{
    return m_colorFlag;
}

void KGlobalData::setBorderWidth(const int borderWidth)
{
    m_pShapeParams->m_borderWidth = borderWidth;
}

int KGlobalData::getBorderWidth() const
{
    return m_pShapeParams->m_borderWidth;
}

void KGlobalData::setBoderColor(const QColor borderColor)
{
    m_pShapeParams->m_borderColor = borderColor;
}

QColor KGlobalData::getBoderColor()
{
    return m_pShapeParams->m_borderColor;
}

void KGlobalData::setFillColor(const QColor fillColor)
{
    m_pShapeParams->m_fillColor = fillColor;
}

QColor KGlobalData::getFillColor()
{
    return m_pShapeParams->m_fillColor;
}

void KGlobalData::setPenStyle(const Qt::PenStyle penStyle)
{
    m_pShapeParams->m_penStyle = penStyle;
}

Qt::PenStyle KGlobalData::getPenStyle() const
{
    return m_pShapeParams->m_penStyle;
}

int KGlobalData::getCanvasWidth() const
{
    return m_pCanvasParams->m_canvasWidth;
}

void KGlobalData::setCanvasWidth(const int width)
{
    m_pCanvasParams->m_canvasWidth = width;
}

int KGlobalData::getCanvasHeight() const
{
    return m_pCanvasParams->m_canvasHeight;
}

void KGlobalData::setCanvasHeight(const int height)
{
    m_pCanvasParams->m_canvasHeight = height;
}

QString KGlobalData::getCanvasColor()
{
    return m_pCanvasParams->m_canvasColor;
}

void KGlobalData::setCanvasColor(const QString& colorStr)
{
    m_pCanvasParams->m_canvasColor = colorStr;
}

int KGlobalData::getPrevCanvasWidth() const
{
    return m_pCanvasParams->m_prevCanvasWidth;
}

void KGlobalData::setPrevCanvasWidth(const int width)
{
    m_pCanvasParams->m_prevCanvasWidth = width;
}

int KGlobalData::getPrevCanvasHeight() const
{
    return m_pCanvasParams->m_prevCanvasHeight;
}

void KGlobalData::setPrevCanvasHeight(const int height)
{
    m_pCanvasParams->m_prevCanvasHeight = height;
}

QString KGlobalData::getPrevCanvasColor()
{
    return m_pCanvasParams->m_prevCanvasColor;
}

void KGlobalData::setPrevCanvasColor(const QString& colorStr)
{
    m_pCanvasParams->m_prevCanvasColor = colorStr;
}

qreal KGlobalData::getCanvasScale() const
{
    return m_pCanvasParams->m_scale;
}

void KGlobalData::setCanvaScale(qreal scale)
{
    m_pCanvasParams->m_scale = scale;
}

QUndoStack* KGlobalData::getUndoStack() 
{
    return &m_undoStack;
}

void KGlobalData::loadButtonTips()
{
    QUrl url("https://m1.apifoxmock.com/m1/6237106-5930859-default/app/buttontips");
    m_pNetworkManager->get(QNetworkRequest(url));
}

void KGlobalData::onButtonTipsDownloaded(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        if (!jsonDoc.isNull() && jsonDoc.isObject()) {
            QJsonObject jsonObj = jsonDoc.object();
            for (auto it = jsonObj.begin(); it != jsonObj.end(); ++it) {
                QString key = it.key();
                QJsonValue value = it.value();
                if (value.isObject()) {
                    QJsonObject tipObj = value.toObject();
                    QString title = tipObj["title"].toString();
                    QString text = tipObj["text"].toString();

                    KButtonFlag flag = KButtonFlag::NoneButtonFlag;
                    if (key == "selectionbutton") flag = KButtonFlag::MouseButtonFlag;
                    else if (key == "freehandlinedrawbutton") flag = KButtonFlag::PenButtonFlag;
                    else if (key == "linedrawbutton") flag = KButtonFlag::LineButtonFlag;
                    else if (key == "rectdrawbutton") flag = KButtonFlag::RectButtonFlag;
                    else if (key == "circledrawbutton") flag = KButtonFlag::CircleButtonFlag;
                    else if (key == "pentagondrawbutton") flag = KButtonFlag::PentButtonFlag;
                    else if (key == "hexadrawbutton") flag = KButtonFlag::HexaButtonFlag;
                    else if (key == "stardrawbutton") flag = KButtonFlag::StarButtonFlag;
                    else if (key == "heartdrawbutton") flag = KButtonFlag::HeartButtonFlag;
                    else if (key == "textdrawbutton") flag = KButtonFlag::TextButtonFlag;
                    else if (key == "zoomoutbutton") flag = KButtonFlag::ZoomButtonFlag;

                    if (flag != KButtonFlag::NoneButtonFlag) {
                        m_buttonTips[flag] = qMakePair(title, text);
                    }
                }
            }
        }
    }
    else {
        qDebug() << "Error downloading button tips:" << reply->errorString();
    }
    reply->deleteLater();
}

QPair<QString, QString> KGlobalData::getButtonTip(KButtonFlag flag) const
{
    if (m_buttonTips.contains(flag)) {
        return m_buttonTips.value(flag);
    }
    return qMakePair(QString(), QString());
}
