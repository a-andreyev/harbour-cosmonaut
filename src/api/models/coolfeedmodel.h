#ifndef COOLFEEDMODEL_H
#define COOLFEEDMODEL_H

#include <QObject>
#include "abstractjsonrestlistmodel.h"
#include "src/api/qtrestrocketapi.h"

class CoolFeedModel : public AbstractJsonRestListModel
{
    Q_OBJECT
    Q_PROPERTY(QString balanceAmount READ balanceAmount NOTIFY balanceAmountChanged)
    Q_PROPERTY(QString balanceCurrencyCode READ balanceCurrencyCode NOTIFY balanceCurrencyCodeChanged)
    Q_PROPERTY(QString miles READ miles WRITE setMiles NOTIFY milesChanged)
    Q_PROPERTY(QString email READ email NOTIFY emailChanged)
    Q_PROPERTY(QString token READ token NOTIFY tokenChanged)

public:
    explicit CoolFeedModel(QObject *parent = 0);

    static void declareQML() {
        AbstractJsonRestListModel::declareQML();
        qmlRegisterType<CoolFeedModel>("harbour.cosmonaut.coolfeed", 1, 0, "CoolFeedModel");
    }

    QString balanceAmount() const;
    QString balanceCurrencyCode() const;
    QString miles() const;
    QString email() const;
    QString token() const;

public slots:

    Q_INVOKABLE void profileRefresh();
    void reload();

signals:
    void balanceAmountChanged(QString balanceAmount);
    void balanceCurrencyCodeChanged(QString BalanceCurrencyCode);
    void milesChanged(QString miles);
    void emailChanged(QString email);

    void tokenChanged(QString token);

protected:
    QVariantList getVariantList(QByteArray bytes);
    QNetworkReply *fetchMoreImpl(const QModelIndex &parent);
    QNetworkReply *fetchDetailImpl(QString id);
    QVariantMap preProcessItem(QVariantMap item);
private:
    void setBalanceCurrencyCode(QString balanceCurrencyCode);
    void setBalanceAmount(QString balanceAmount);
    void setMiles(QString miles);

    QString _balanceAmount;
    QString _balanceCurrencyCode;
    QString _miles;
    QString _email;
    QString _token;

    static bool _compareFeedObj(const QVariant &first, const QVariant& second);
};

#endif // COOLFEEDMODEL_H
