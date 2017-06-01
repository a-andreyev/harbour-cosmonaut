#include "qtrestrocketapi.h"
#include <QFile>
//#include <QTextStream>
#include <QCryptographicHash>
#include <QDateTime>

QtRestRocketAPI::QtRestRocketAPI() : APIBase(0)
{
    _hashPrefix = "0Jk211uvxyyYAFcSSsBK3+etfkDPKMz6asDqrzr+f7c=_";
    _hashSuffix = "_dossantos";
    _coolFeedPath = "/operations/cool_feed";
    setAcceptHeader(QString("Content-Type").toUtf8());
}

QNetworkRequest QtRestRocketAPI::createRequest(const QUrl &url) const
{
    QNetworkRequest request;
    request.setRawHeader(QString("X-Device-ID").toUtf8(),QString("ROCKCLI_74e543dcb7e6").toUtf8()); // TODO
    request.setHeader(QNetworkRequest::UserAgentHeader,QString("RocketScience/5 (ale@songbee.net)").toUtf8()); // TODO

    QDateTime currentDateTime = QDateTime::currentDateTimeUtc();
    uint unixtime = currentDateTime.toTime_t();
    QString timestamp = QString::number(unixtime);
    QString pass = _hashPrefix+timestamp+_hashSuffix;
    QString xSig = QString(
                QCryptographicHash::hash(pass.toUtf8(),
                                         QCryptographicHash::Md5).toHex());
    request.setRawHeader(QString("X-Sig").toUtf8(),xSig.toUtf8());
    request.setRawHeader(QString("X-Time").toUtf8(),timestamp.toUtf8());
    request.setUrl(url);
    qDebug() << timestamp << url;
    return request;
}

QNetworkReply *QtRestRocketAPI::handleRequest(QString path, QStringList sort, Pagination *pagination, QVariantMap filters, QStringList fields, QString id)
{
    if (path == _coolFeedPath) {
        return getFeed(sort, pagination, filters, fields);
    }
}

QNetworkReply *QtRestRocketAPI::getFeed(QStringList sort, Pagination *pagination, QVariantMap filters, QStringList fields)
{
    QUrl url = QUrl(baseUrl()+_coolFeedPath);

    QNetworkReply *reply = get(url);
    return reply;
}
