#include "qtrestrocketapi.h"
#include <QFile>
//#include <QTextStream>
#include <QCryptographicHash>
#include <QDateTime>

QtRestRocketAPI::QtRestRocketAPI() : APIBase(0)
{
    _loginPath = "/login";
    _tokenPrefix = "Token token=";
    _hashPrefix = "0Jk211uvxyyYAFcSSsBK3+etfkDPKMz6asDqrzr+f7c=_";
    _hashSuffix = "_dossantos";
    _coolFeedPath = "/operations/cool_feed";
    setAcceptHeader(QString("Content-Type").toUtf8());
}

QNetworkRequest QtRestRocketAPI::createRequest(const QUrl &url) const
{
    QNetworkRequest request;
    // TODO: move app name to constans and add option to hash phone number
    request.setRawHeader(QString("X-Device-ID").toUtf8(),QString("ROCKCLI_74e543dcb7e6").toUtf8());
    // TODO: change useragent
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

    qDebug()<<"tok:"<<_token;

    if (_token.isEmpty()) {
        QUrl loginUrl = QUrl(baseUrl()+_loginPath);
        QUrlQuery query;
        query.addQueryItem("email", _email);
        query.addQueryItem("password", _pin);
        loginUrl.setQuery(query.query());
        request.setUrl(loginUrl);
    }
    else {
        request.setUrl(url);
    }
    // qDebug() << timestamp << url;
    return request;
}

QNetworkReply *QtRestRocketAPI::handleRequest(QString path, QStringList sort, Pagination *pagination, QVariantMap filters, QStringList fields, QString id)
{
    if (path == _coolFeedPath) {
        return getFeed(sort, pagination, filters, fields);
    }
    // TODO: null
}

QNetworkReply *QtRestRocketAPI::getFeed(QStringList sort, Pagination *pagination, QVariantMap filters, QStringList fields)
{
    QUrl url = QUrl(baseUrl()+_coolFeedPath);

    QNetworkReply *reply = get(url);
    return reply;
}

void QtRestRocketAPI::replyError(QNetworkReply::NetworkError error)
{
    qDebug()<<error;
    if (error==QNetworkReply::AuthenticationRequiredError) {
        _token = ""; // FIXME: token as q_property
        emit authRequested();
    }
}

void QtRestRocketAPI::login(QString email, QString pin)
{
    _pin = pin;
    _email  = email;
}

void QtRestRocketAPI::setAuthTokenCode(QString authTokenCode)
{
    _token = authTokenCode;
    setAuthToken(QString(_tokenPrefix+_token).toUtf8());
}
