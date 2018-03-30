#ifndef QTRESTROCKETAPI_H
#define QTRESTROCKETAPI_H

#include "apibase.h"
#include <QtQml>
#include <QUrlQuery>
#include <QLatin1String>
#include <QSettings>

class QtRestRocketAPI : public APIBase
{
    Q_OBJECT
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(QString token READ token WRITE setToken NOTIFY tokenChanged)

    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName NOTIFY firstNameChanged)
    // TODO: ProfileModel
    // cash_out_count
    Q_PROPERTY(int cashOutCount READ cashOutCount WRITE setCashOutCount NOTIFY cashOutCountChanged)
    // free_cash_out_limit
    Q_PROPERTY(int freeCashOutLimit READ freeCashOutLimit WRITE setFreeCashOutLimit NOTIFY freeCashOutLimitChanged)

public:
    Q_INVOKABLE explicit QtRestRocketAPI();

    static void declareQML() {
        qmlRegisterType<QtRestRocketAPI>("harbour.cosmonaut.qtrestrocketapi",
                                         1, 0, "QtRestRocketAPI");
    }

    QNetworkRequest createRequest(const QUrl &url) const;

    //requests
    QNetworkReply *handleRequest(QString path, QStringList sort,
                                 Pagination *pagination,
                                 QVariantMap filters = QVariantMap(),
                                 QStringList fields = QStringList(),
                                 QString id = 0);

    // feed
    // balance
    // register
    // tariffs
    // transfer

    //get list of objects
    QNetworkReply *getFeed(QStringList sort, Pagination *pagination,
                           QVariantMap filters = QVariantMap(),
                           QStringList fields = QStringList());

    QNetworkReply *getProfile();
    QString email() const;
    QString token() const;
    QString firstName() const;

    int cashOutCount() const;
    int freeCashOutLimit() const;

signals:
    void registrationRequested();
    void rocketCodeRequested();
    void smsCodeRequested();
    void registered();
    void loggedIn();
    void serverError(QString description);
    void serverMessage(QString description);

    void emailChanged(QString email);
    void tokenChanged(QString token);
    void firstNameChanged(QString firstName);

    void cashOutCountChanged(int cashOutCount);
    void freeCashOutLimitChanged(int freeCashOutLimit);

public slots:
    void profileRefresh();
    void profileRefreshFinished();
    void login(QString pin);
    void loginFinished();
    void requestSMS(QString phone);
    void requestSMSFinished();
    void verifySMSCode(QString smsCode);
    void verifySMSCodeFinished();
    void setAuthTokenCode(QString authTokenCode);

    void setEmail(QString email);
    void setToken(QString token);
    void setFirstName(QString firstName);

    void saveRegistation();

    void setCashOutCount(int cashOutCount);
    void setFreeCashOutLimit(int freeCashOutLimit);

protected slots:
    void replyError(QNetworkReply::NetworkError error);

private:
    QString _userAgent;
    QString _profilePath;
    QString _coolFeedPath;
    QString _loginPath;
    QString _deviceRegisterPath;
    QString _verifySMSPrefix;
    QString _verifySMSSuffix;
    QString _hashPrefix;
    QString _hashSuffix;
    QString _tokenPrefix;
    QString _token;
    QString _email;
    QString _smsId;
    QString _deviceID;
    int _cashOutCount;
    int _freeCashOutLimit;
    QSettings *_settings;
    // fieds:
    QString _organizationFieldName;
    QString _appFieldName;
    QString _xDeviceIdFieldName;
    QString _xSigFieldName;
    QString _xTimeFieldName;
    QString _xWWWFormUrlencodedContentTypeName;
    QString _jsonContentTypeName;
    QString _responseFieldName;
    QString _descriptionFieldName;
    QString _showItFieldName;
    QString _emailFieldName;
    QString _passwordFieldName;
    QString _tokenFieldName;
    QString _smsVerificationFieldName;
    QString _codeJsonString;
    QString _phoneJsonString;
    QString _statusFieldName;
    QString _userFieldName;
    QString _firstNameFieldName;
    QString _idFieldName;
    QString _firstName;

    QString _cashOutCountFieldName;
    QString _freeCashOutLimitFieldName;
};

#endif // QTRESTROCKETAPI_H
