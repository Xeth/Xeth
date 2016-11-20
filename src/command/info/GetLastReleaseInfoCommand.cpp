#include "GetLastReleaseInfoCommand.hpp"

namespace Xeth{


QVariant GetLastReleaseInfoCommand::operator()() const
{

    return QVariant::fromValue(getJson().toVariantMap());
}


QJsonObject GetLastReleaseInfoCommand::getJson() const
{
    QEventLoop eventLoop;
    QTimer timer;

    QUrl url("http://bitprofile.github.io/xeth/latest.json");
    
    QNetworkRequest request(url);
    QNetworkAccessManager manager;

    QObject::connect(&timer, &QTimer::timeout, &eventLoop, &QEventLoop::quit);
    QObject::connect(&manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    timer.setSingleShot(true);
    timer.start(5000);

    QNetworkReply *reply = manager.get(request);

    if(reply == NULL)
    {
        throw std::runtime_error("network error");
    }
    eventLoop.exec();

    if(reply->error() != QNetworkReply::NoError)
    {
        throw std::runtime_error("failed to fetch latest.json");
    }

    QByteArray content = reply->readAll();
    QJsonDocument document = QJsonDocument::fromJson(content);
    if(document.isNull())
    {
        throw std::runtime_error("invalid latest.json document");
    }
    return document.object();
}


}

