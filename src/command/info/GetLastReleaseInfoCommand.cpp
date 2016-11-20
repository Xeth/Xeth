#include "GetLastReleaseInfoCommand.hpp"
#include <QDebug>

namespace Xeth{


QVariant GetLastReleaseInfoCommand::operator()() const
{

    return QVariant::fromValue(getJson().toVariantMap());
}


QJsonObject GetLastReleaseInfoCommand::getJson() const
{
    QEventLoop eventLoop;
    QTimer timer;

    QUrl url("http://xeth.org/latest.json");
    QNetworkRequest request(url);
    QNetworkAccessManager manager;

    QObject::connect(&timer, &QTimer::timeout, &eventLoop, &QEventLoop::quit);
    QObject::connect(&manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    timer.setSingleShot(true);
    timer.start(5000);

    QNetworkReply *reply = manager.get(request);

    if(reply == NULL)
    {
        qDebug()<<"network error";
        throw std::runtime_error("network error");
    }
    eventLoop.exec();

    if(reply->error() != QNetworkReply::NoError)
    {
        qDebug()<<"failed to fetch latest.json";
        throw std::runtime_error("failed to fetch latest.json");
    }
    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    if(document.isNull())
    {
        qDebug()<<"invalid latest json document";
        throw std::runtime_error("invalid latest.json document");
    }
    qDebug()<<"got data : "<<document.object();
    return document.object();
}


}

