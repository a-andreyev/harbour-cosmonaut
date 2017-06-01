#include "coolfeedmodel.h"

CoolFeedModel::CoolFeedModel(QObject *parent) : AbstractJsonRestListModel(parent)
{

}

QString CoolFeedModel::balanceAmount() const
{
    qDebug()<<"gettin"<<m_balanceAmount;
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
    qDebug()<<"balanceAmount::"<<balanceAmount;
    if (m_balanceAmount == balanceAmount)
        return;

    m_balanceAmount = balanceAmount;
    qDebug()<<"balanceAmountChanged(balanceAmount)"<<balanceAmount;
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

    // FIXME: magic strings

    setMiles(jsonObject.value(QString("miles")).toString());
    QJsonObject balanceObject = jsonObject.value(QString("balance")).toObject();
    qDebug()<<"balanceObject::"<<balanceObject;
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
    qDebug() << "feedArray.count()" << feedArray.count();

    return feedArray.toVariantList();
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
    qDebug()<<item;
    return item;
}
