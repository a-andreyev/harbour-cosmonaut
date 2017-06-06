#include "coolfeedmodel.h"

CoolFeedModel::CoolFeedModel(QObject *parent) : AbstractJsonRestListModel(parent)
{
    // FIXME:
    setEmail("myEmail");

    // api.setAuthTokenCode(token)
}

QString CoolFeedModel::balanceAmount() const
{
    return m_balanceAmount;
}

QString CoolFeedModel::balanceCurrencyCode() const
{
    return m_balanceCurrencyCode;
}

QString CoolFeedModel::miles() const
{
    return m_miles;
}

QString CoolFeedModel::email() const
{
    return m_email;
}

QString CoolFeedModel::token() const
{
    return m_token;
}

void CoolFeedModel::setEmail(QString email)
{
    if (m_email == email)
        return;

    m_email = email;
    emit emailChanged(email);
}

void CoolFeedModel::setToken(QString token)
{
    if (m_token == token)
        return;

    m_token = token;
    emit tokenChanged(token);
}

void CoolFeedModel::login(QString pin)
{
    static_cast<QtRestRocketAPI *>(apiInstance())->login(m_email,pin);
    reload();
}

void CoolFeedModel::setMiles(QString miles)
{
    if (m_miles == miles)
        return;

    m_miles = miles;
    emit milesChanged(miles);
}

void CoolFeedModel::setBalanceCurrencyCode(QString balanceCurrencyCode)
{
    if (m_balanceCurrencyCode == balanceCurrencyCode)
        return;

    m_balanceCurrencyCode = balanceCurrencyCode;
    emit balanceCurrencyCodeChanged(balanceCurrencyCode);
}

void CoolFeedModel::setBalanceAmount(QString balanceAmount)
{
    if (m_balanceAmount == balanceAmount)
        return;

    m_balanceAmount = balanceAmount;
    emit balanceAmountChanged(balanceAmount);
}

QVariantList CoolFeedModel::getVariantList(QByteArray bytes)
{
    QString str = QString::fromUtf8(bytes.data(), bytes.size());

    //qDebug()<<str;

    QJsonParseError parseError;
    QJsonDocument document = QJsonDocument::fromJson(bytes, &parseError);
    QJsonObject jsonObject = document.object();

    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << parseError.errorString();
    }

    // TODO: get rid of magic strings

    qDebug()<<jsonObject;

    QString token = jsonObject.value(QString("token")).toString();
    if (!token.isEmpty()) {
        setToken(token);
        return QJsonArray().toVariantList();
    }
    else {
        setEmail(jsonObject.value(QString("email")).toString());

        setMiles(QString::number(jsonObject.value(QString("miles")).toDouble()));
        QJsonObject balanceObject = jsonObject.value(QString("balance")).toObject();
        setBalanceAmount(QString::number(balanceObject.value(QString("amount")).toDouble()));
        setBalanceCurrencyCode(balanceObject.value(QString("currency_code")).toString());

        QJsonValue dates = jsonObject.value(QString("dates"));
        //qDebug<< dates;
        QJsonArray feedArray;
        foreach (QJsonValue dateValue, dates.toObject()) {
            foreach (QJsonValue feedItem, dateValue.toArray()) {
                feedArray.append(feedItem);
            }
        }

        return feedArray.toVariantList();
    }
}

QNetworkReply *CoolFeedModel::fetchMoreImpl(const QModelIndex &parent)
{
    Q_UNUSED(parent)
    return static_cast<QtRestRocketAPI *>(apiInstance())->getFeed(sort(), pagination(), filters(), fields());
}

QNetworkReply *CoolFeedModel::fetchDetailImpl(QString id)
{
    // FIXME:
    Q_UNUSED(id)
    return static_cast<QtRestRocketAPI *>(apiInstance())->getFeed(sort(), pagination(), filters(), fields());
}

QVariantMap CoolFeedModel::preProcessItem(QVariantMap item)
{
    // TODO
    //qDebug()<<item;
    return item;
}
