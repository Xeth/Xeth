#include "Notifier.hpp"

namespace Xeth{

Notifier::Notifier()
{}



void Notifier::emitData(const QString &context, const QString &uri, const QString &key, const QVariant &value)
{
    QVariantMap event;
    event["context"] = context;
    event["uri"] = uri;
    event["key"] = key;
    event["value"] = value;
    emit Data(event);
}


void Notifier::emitData(const QString &context, const QString &key, const QVariant &value)
{
    QVariantMap event;
    event["context"] = context;
    event["key"] = key;
    event["value"] = value;
    emit Data(event);
}


void Notifier::emitError(const QString &msg)
{
    QVariantMap event;
    event["message"] = msg;
    emit Error(event);
}

void Notifier::emitError(const QString &context, const QString &msg)
{
    QVariantMap event;
    event["context"] = context;
    event["message"] = msg;
    emit Error(event);
}

void Notifier::emitObjectError(const QString &context, const QString &uri, const QString &msg)
{
    QVariantMap event;
    event["context"] = context;
    event["message"] = msg;
    event["uri"] = uri;
    emit Error(event);
}


void Notifier::emitMessage(const QString &msg)
{
    emit Message(msg);
}


void Notifier::emitReady()
{
    qDebug()<<"emitting ready signal";
    emit Ready();
}




}
