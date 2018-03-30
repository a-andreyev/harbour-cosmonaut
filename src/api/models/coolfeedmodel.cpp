#include "coolfeedmodel.h"
#include <QDateTime>
#include <algorithm>

CoolFeedModel::CoolFeedModel(QObject *parent) : AbstractJsonRestListModel(parent)
{
    //connect(static_cast<QtRestRocketAPI *>(apiInstance()),&QtRestRocketAPI::reloadModels,
    //        this,&CoolFeedModel::reload);
    // FIXME:
    // setEmail("myEmail");

    // api.setAuthTokenCode(token)
}

QString CoolFeedModel::balanceAmount() const
{
    return _balanceAmount;
}

QString CoolFeedModel::balanceCurrencyCode() const
{
    return _balanceCurrencyCode;
}

QString CoolFeedModel::miles() const
{
    return _miles;
}

QString CoolFeedModel::email() const
{
    return _email;
}

QString CoolFeedModel::token() const
{
    return _token;
}

void CoolFeedModel::profileRefresh()
{
    static_cast<QtRestRocketAPI *>(apiInstance())->profileRefresh();
}

void CoolFeedModel::reload()
{
    profileRefresh();
    AbstractJsonRestListModel::reload();
}

void CoolFeedModel::setMiles(QString miles)
{
    if (_miles == miles)
        return;

    _miles = miles;
    emit milesChanged(miles);
}

bool CoolFeedModel::_compareFeedObj(const QVariant &first, const QVariant &second)
{
    return second.toJsonObject().value(QStringLiteral("happened_at")).toDouble() <
            first.toJsonObject().value(QStringLiteral("happened_at")).toDouble();
}

void CoolFeedModel::setBalanceCurrencyCode(QString balanceCurrencyCode)
{
    if (_balanceCurrencyCode == balanceCurrencyCode)
        return;

    _balanceCurrencyCode = balanceCurrencyCode;
    emit balanceCurrencyCodeChanged(balanceCurrencyCode);
}

void CoolFeedModel::setBalanceAmount(QString balanceAmount)
{
    if (_balanceAmount == balanceAmount)
        return;

    _balanceAmount = balanceAmount;
    emit balanceAmountChanged(balanceAmount);
}

QVariantList CoolFeedModel::getVariantList(QByteArray bytes)
{
    QVariantList feedList;
    //QString str = QString::fromUtf8(bytes.data(), bytes.size());

    //qDebug()<<Q_FUNC_INFO<<str;

    QJsonParseError parseError;
    QJsonDocument document = QJsonDocument::fromJson(bytes, &parseError);
    QJsonObject jsonObject = document.object();

    if (parseError.error != QJsonParseError::NoError) {
        return feedList;
        // qDebug() << parseError.errorString();
    }

    // TODO: get rid of magic strings (QStringLiteral or QLatin1String)

    // qDebug()<<jsonObject;

    setMiles(QString::number(jsonObject.value(QString("miles")).toDouble()));
    QJsonObject balanceObject = jsonObject.value(QString("balance")).toObject();
    setBalanceAmount(QString::number(balanceObject.value(QString("amount")).toDouble()));
    setBalanceCurrencyCode(balanceObject.value(QString("currency_code")).toString());

    QJsonObject datesObj = jsonObject.value(QStringLiteral("dates")).toObject();
    foreach (QString key, datesObj.keys()) {
        foreach (QJsonValue feedItem, datesObj.value(key).toArray()) {
            QJsonObject feedObj = feedItem.toObject();
            /*
            QStringList d = key.split("-");
            QDate date = QDate(QString(d.at(0)).toInt(),
                               QString(d.at(1)).toInt(),
                               QString(d.at(2)).toInt());
            */
            int ms = feedObj.value(QStringLiteral("happened_at")).toInt();
            QDateTime happenedAt;
            happenedAt.setTime_t(ms);
            feedObj.remove(QStringLiteral("happened_at"));
            feedObj.insert(QStringLiteral("happened_at"),happenedAt.toMSecsSinceEpoch());
            feedObj.insert(QStringLiteral("happened_at_date_string"),happenedAt.toString("dd.MM.yyyy"));
            feedList.append(feedObj);
        }
    }
    std::sort(feedList.begin(), feedList.end(), _compareFeedObj);
    return feedList;
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
