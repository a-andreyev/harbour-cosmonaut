#include "qtrestrocketapi.h"
#include <QFile>
//#include <QTextStream>
#include <QCryptographicHash>
#include <QDateTime>
#include <QtSystemInfo>

QtRestRocketAPI::QtRestRocketAPI() : APIBase(0)
{
    //fields:
    _organizationFieldName = QStringLiteral("aa13q");
    _appFieldName = QStringLiteral("cosmonaut");
    _xDeviceIdFieldName = QStringLiteral("X-Device-ID");
    _xSigFieldName = QStringLiteral("X-Sig");
    _xTimeFieldName = QStringLiteral("X-Time");
    _xWWWFormUrlencodedContentTypeName = QStringLiteral("application/x-www-form-urlencoded");
    _jsonContentTypeName = QStringLiteral("application/json");
    _responseFieldName = QStringLiteral("response");
    _descriptionFieldName = QStringLiteral("description");
    _showItFieldName = QStringLiteral("show_it");
    _emailFieldName = QStringLiteral("email");
    _passwordFieldName = QStringLiteral("password");
    _tokenFieldName = QStringLiteral("token");
    _smsVerificationFieldName = QStringLiteral("sms_verification");
    _codeJsonString = QStringLiteral("{\"code\":\"%1\"}");
    _phoneJsonString = QStringLiteral("{\"phone\":\"%1\"}");
    _statusFieldName = QStringLiteral("status");
    _userFieldName = QStringLiteral("user");
    _firstNameFieldName = QStringLiteral("first_name");
    _idFieldName = QStringLiteral("id");

    _cashOutCountFieldName = QStringLiteral("cash_out_count");
    _freeCashOutLimitFieldName = QStringLiteral("free_cash_out_limit");

    _userAgent = QStringLiteral("Cosmonaut/5 (aa13q@ya.ru)");
    _profilePath = QStringLiteral("/profile");
    _coolFeedPath = QStringLiteral("/operations/cool_feed");
    _loginPath = QStringLiteral("/login");
    _deviceRegisterPath = QStringLiteral("/devices/register");
    _verifySMSPrefix = QStringLiteral("/sms_verifications/");
    _verifySMSSuffix = QStringLiteral("/verify");
    _tokenPrefix = QStringLiteral("Token token=");
    _hashPrefix = QStringLiteral("0Jk211uvxyyYAFcSSsBK3+etfkDPKMz6asDqrzr+f7c=_");
    _hashSuffix = QStringLiteral("_dossantos");

    QDeviceInfo *systemDeviceInfo = new QDeviceInfo(this);
    _deviceID = QStringLiteral("COSMONAUT_%1").arg(systemDeviceInfo->uniqueDeviceID().remove(QChar('-')).right(12));
    systemDeviceInfo->deleteLater();
    // qDebug()<<Q_FUNC_INFO<<_deviceID;

    _settings = new QSettings(_organizationFieldName,_appFieldName,this);
    // qDebug()<<Q_FUNC_INFO<<_settings->fileName();

    setToken(_settings->value(_tokenFieldName).toString());
    setEmail(_settings->value(_emailFieldName).toString());
    setFirstName(_settings->value(_firstNameFieldName).toString());
}



QNetworkRequest QtRestRocketAPI::createRequest(const QUrl &url) const
{
    //qDebug()<<Q_FUNC_INFO<<url.path();

    QNetworkRequest request;
    request.setRawHeader(_xDeviceIdFieldName.toUtf8(),_deviceID.toUtf8());
    request.setHeader(QNetworkRequest::UserAgentHeader,_userAgent.toUtf8());

    QDateTime currentDateTime = QDateTime::currentDateTimeUtc();
    uint unixtime = currentDateTime.toTime_t();
    QString timestamp = QString::number(unixtime);
    QString pass = _hashPrefix+timestamp+_hashSuffix;
    QString xSig = QString(
                QCryptographicHash::hash(pass.toUtf8(),
                                         QCryptographicHash::Md5).toHex());
    request.setRawHeader(_xSigFieldName.toUtf8(),xSig.toUtf8());
    request.setRawHeader(_xTimeFieldName.toUtf8(),timestamp.toUtf8());

    if (url.toString().endsWith(_coolFeedPath)) {
        request.setHeader(QNetworkRequest::ContentTypeHeader, _xWWWFormUrlencodedContentTypeName);
    }
    else {
        request.setHeader(QNetworkRequest::ContentTypeHeader, _jsonContentTypeName);
    }

    request.setUrl(url);
    // qDebug() << timestamp << url;
    return request;
}

QNetworkReply *QtRestRocketAPI::handleRequest(QString path, QStringList sort, Pagination *pagination, QVariantMap filters, QStringList fields, QString id)
{
    // qDebug()<<Q_FUNC_INFO<<path;
    return Q_NULLPTR;
}

QNetworkReply *QtRestRocketAPI::getFeed(QStringList sort, Pagination *pagination, QVariantMap filters, QStringList fields)
{
    QUrl url = QUrl(baseUrl()+_coolFeedPath);

    QNetworkReply *reply = get(url);
    return reply;
}

QNetworkReply *QtRestRocketAPI::getProfile()
{
    QUrl url = QUrl(baseUrl()+_profilePath);

    QNetworkReply *reply = get(url);
    return reply;
}

QString QtRestRocketAPI::email() const
{
    return _email;
}

QString QtRestRocketAPI::token() const
{
    return _token;
}

QString QtRestRocketAPI::firstName() const
{
    return _firstName;
}

int QtRestRocketAPI::cashOutCount() const
{
    return _cashOutCount;
}

int QtRestRocketAPI::freeCashOutLimit() const
{
    return _freeCashOutLimit;
}

void QtRestRocketAPI::profileRefresh()
{
    QNetworkReply *reply = getProfile();
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(replyError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(finished()), this, SLOT(profileRefreshFinished()));
}

void QtRestRocketAPI::profileRefreshFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    QByteArray answer = reply->readAll();

    QJsonParseError parseError;
    QJsonDocument document = QJsonDocument::fromJson(answer, &parseError);
    QJsonObject jsonObject = document.object();

    if (parseError.error != QJsonParseError::NoError) {
        // qDebug() << parseError.errorString();
        return;
    }

    QString accountNumber = jsonObject.value(QString("user")).toObject()
            .value(QString("account_details")).toObject().value(QString("account")).toString();

    if (accountNumber.isEmpty()) {
        return;
    }
    foreach (QJsonValue account, jsonObject.value(QString("user")).toObject()
             .value(QString("accounts")).toArray()) {
        QJsonObject accountObj = account.toObject();
        if (accountObj
                .value(QString("account_details")).toObject()
                .value(QString("account")).toString()==accountNumber) {
            setCashOutCount(accountObj.value(QString("cash_out_count")).toInt());
            setFreeCashOutLimit(accountObj.value(QString("free_cash_out_limit")).toInt());
        }
    }


}

void QtRestRocketAPI::replyError(QNetworkReply::NetworkError error)
{
    // qDebug()<<error;
    if (error==QNetworkReply::AuthenticationRequiredError) {
        setToken(QStringLiteral(""));
        emit rocketCodeRequested();
    }
    else if (error==QNetworkReply::ProtocolInvalidOperationError) {
        QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
        QByteArray answer = reply->readAll();
        QJsonDocument itemDoc = QJsonDocument::fromJson(answer);
        QJsonObject rootObject = itemDoc.object();
        QJsonValue response = rootObject.value(_responseFieldName);
        QJsonObject responseObj = response.toObject();
        QString description = responseObj.value(_descriptionFieldName).toString();
        if (responseObj.value(_showItFieldName).toBool()) {
            emit serverError(description);
        }
    }
}

void QtRestRocketAPI::login(QString pin)
{
    // qDebug()<<Q_FUNC_INFO<<pin;
    QUrl loginUrl = QUrl(baseUrl()+_loginPath);
    QUrlQuery query;
    query.addQueryItem(_emailFieldName, _email);
    query.addQueryItem(_passwordFieldName, pin);
    loginUrl.setQuery(query.query());

    QNetworkReply *reply = get(loginUrl);
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(replyError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(finished()), this, SLOT(loginFinished()));
}

void QtRestRocketAPI::loginFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    QByteArray answer = reply->readAll();

    QJsonDocument itemDoc = QJsonDocument::fromJson(answer);
    QJsonObject rootObject = itemDoc.object();
    // qDebug()<<Q_FUNC_INFO<<rootObject;
    setToken(rootObject.value(_tokenFieldName).toString());
}

void QtRestRocketAPI::requestSMS(QString phone)
{
    QString phoneData = _phoneJsonString.arg(phone);
    // qDebug()<<Q_FUNC_INFO<<phoneData;
    QNetworkReply *reply = post(QUrl(baseUrl()+_deviceRegisterPath), phoneData.toUtf8());
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(replyError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(finished()), this, SLOT(requestSMSFinished()));
}

void QtRestRocketAPI::requestSMSFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    QByteArray answer = reply->readAll();
    // qDebug()<<Q_FUNC_INFO<<answer;

    QJsonDocument itemDoc = QJsonDocument::fromJson(answer);
    QJsonObject rootObject = itemDoc.object();
    QJsonValue response = rootObject.value(_responseFieldName);
    QJsonObject responseObj = response.toObject();
    QString description = responseObj.value(_descriptionFieldName).toString();
    emit serverMessage(description);
    int status = responseObj.value(_statusFieldName).toInt();
    if (status==200) {
        QJsonValue smsVerification = rootObject.value(_smsVerificationFieldName);
        QJsonObject smsObj = smsVerification.toObject();
        QString id = smsObj.value(_idFieldName).toString();
        _smsId = id;
        // qDebug()<<Q_FUNC_INFO<<_smsId;
    }
}

void QtRestRocketAPI::verifySMSCode(QString smsCode)
{
    QString codeData = _codeJsonString.arg(smsCode);
    // qDebug()<<Q_FUNC_INFO<<codeData;
    QNetworkReply *reply = patch(QUrl(baseUrl()+_verifySMSPrefix+_smsId+_verifySMSSuffix), codeData.toUtf8());
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(replyError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(finished()), this, SLOT(verifySMSCodeFinished()));
}

void QtRestRocketAPI::verifySMSCodeFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    QByteArray answer = reply->readAll();
    // qDebug()<<Q_FUNC_INFO<<answer;

    QJsonDocument itemDoc = QJsonDocument::fromJson(answer);
    QJsonObject rootObject = itemDoc.object();
    QJsonValue response = rootObject.value(_responseFieldName);
    QJsonObject responseObj = response.toObject();
    QString description = responseObj.value(_descriptionFieldName).toString();
    emit serverMessage(description);
    int status = responseObj.value(_statusFieldName).toInt();
    // qDebug()<<Q_FUNC_INFO<<status;
    if (status==200) {
        QJsonValue user = rootObject.value(_userFieldName);
        QJsonObject userObj = user.toObject();
        setEmail(userObj.value(_emailFieldName).toString());
        setFirstName(userObj.value(_firstNameFieldName).toString());
    }

}

void QtRestRocketAPI::setAuthTokenCode(QString authTokenCode)
{
    setAuthToken(QString(_tokenPrefix+authTokenCode).toUtf8());
}

void QtRestRocketAPI::setEmail(QString email)
{
    // qDebug()<<Q_FUNC_INFO<<email;
    if (email.isEmpty()) {
        // qDebug()<<Q_FUNC_INFO;
        emit registrationRequested();
        return;
    }
    if (_email == email)
        return;
    _email = email;
    emit emailChanged(_email);
}

void QtRestRocketAPI::setToken(QString token)
{
    if (_token == token)
        return;
    if (!token.isEmpty()) {
        _token = token;
        setAuthTokenCode(_token);
        emit tokenChanged(_token);
        emit loggedIn();
    }
    // TODO: save token option
    /*
    if (token.isEmpty()) {
        _settings->remove(_tokenFieldName);
    }
    else {
        _settings->setValue(_tokenFieldName,_token);
    }
    */
}

void QtRestRocketAPI::setFirstName(QString firstName)
{
    if (_firstName == firstName)
        return;
    _firstName = firstName;
    emit firstNameChanged(firstName);
}

void QtRestRocketAPI::saveRegistation()
{
    if (_email.isEmpty()) {
        _settings->remove(_emailFieldName);
    }
    else {
        _settings->setValue(_emailFieldName,_email);
    }
    if (_firstName.isEmpty()) {
        _settings->remove(_firstNameFieldName);
    }
    else {
        _settings->setValue(_firstNameFieldName,_firstName);
    }
    emit registered();
}

void QtRestRocketAPI::setCashOutCount(int cashOutCount)
{
    if (_cashOutCount == cashOutCount)
        return;

    _cashOutCount = cashOutCount;
    emit cashOutCountChanged(_cashOutCount);
}

void QtRestRocketAPI::setFreeCashOutLimit(int freeCashOutLimite)
{
    if (_freeCashOutLimit == freeCashOutLimite)
        return;

    _freeCashOutLimit = freeCashOutLimite;
    emit freeCashOutLimitChanged(_freeCashOutLimit);
}

void QtRestRocketAPI::clearSettings()
{
    _settings->clear();
}
