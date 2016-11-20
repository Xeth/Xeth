#pragma once 


#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QTimer>
#include <QVariantMap>
#include <QJsonDocument>
#include <QJsonObject>



namespace Xeth{


class GetLastReleaseInfoCommand
{
    public:
        QVariant operator()() const;
};

}
