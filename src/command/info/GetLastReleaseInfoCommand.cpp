#include "GetLastReleaseInfoCommand.hpp"


namespace Xeth{


QVariant GetLastReleaseInfoCommand::operator()() const
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
        throw std::runtime_error("network error");
    }
    eventLoop.exec();

    if(reply->error() != QNetworkReply::NoError)
    {
        throw std::runtime_error("failed to fetch latest.json");
    }
    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    if(document.isNull())
    {
        throw std::runtime_error("invalid latest.json document");
    }
    return QVariant::fromValue(document.object().toVariantMap());
}


}
