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

public:
    explicit CoolFeedModel(QObject *parent = 0);

    static void declareQML() {
        AbstractJsonRestListModel::declareQML();
        qmlRegisterType<CoolFeedModel>("harbour.cosmonaut.coolfeed", 1, 0, "CoolFeedModel");
    }

    QString balanceAmount() const;
    QString balanceCurrencyCode() const;
    QString miles() const;

public slots:

signals:
    void balanceAmountChanged(QString balanceAmount);
    void balanceCurrencyCodeChanged(QString BalanceCurrencyCode);

    void milesChanged(QString miles);

protected:
    QVariantList getVariantList(QByteArray bytes);
    QNetworkReply *fetchMoreImpl(const QModelIndex &parent);
    QNetworkReply *fetchDetailImpl(QString id);
    QVariantMap preProcessItem(QVariantMap item);
private:
    void setBalanceCurrencyCode(QString balanceCurrencyCode);
    void setBalanceAmount(QString balanceAmount);
    void setMiles(QString miles);

    QString m_balanceAmount;
    QString m_balanceCurrencyCode;
    QString m_miles;
};

#endif // COOLFEEDMODEL_H
