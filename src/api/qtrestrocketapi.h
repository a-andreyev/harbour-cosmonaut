#ifndef QTRESTROCKETAPI_H
#define QTRESTROCKETAPI_H

#include "apibase.h"
#include <QtQml>
#include <QUrlQuery>

class QtRestRocketAPI : public APIBase
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit QtRestRocketAPI();

    static void declareQML() {
        qmlRegisterType<QtRestRocketAPI>("harbour.cosmonaut.qtrestrocketapi", 1, 0, "QtRestRocketAPI");
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
signals:
    void authRequested();

public slots:
    void login(QString email, QString pin);
    void setAuthTokenCode(QString authTokenCode);

protected slots:
    void replyError(QNetworkReply::NetworkError error);

private:
    QString _coolFeedPath;
    QString _loginPath;
    QString _hashPrefix;
    QString _hashSuffix;
    QString _tokenPrefix;
    QString _token;
    QString _pin;
    QString _email;
};

#endif // QTRESTROCKETAPI_H
