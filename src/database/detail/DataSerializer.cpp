#include "DataSerializer.hpp"


namespace Xeth{

/* QJsonObject serialization */

QJsonObject DataSerializer<QJsonObject>::operator()(const char *key, const char *value) const
{
    QJsonDocument document = QJsonDocument::fromJson(value);
    return document.object();
}


bool DataSerializer<QJsonObject>::operator()(const char *key, const char *value, QJsonObject &result) const
{
    QJsonDocument document = QJsonDocument::fromJson(value);
    result = document.object();
    return true;
}


std::string DataSerializer<QJsonObject>::operator ()(const QJsonObject &object) const
{
    QJsonDocument document(object);
    return document.toJson().toStdString();
}


/* std::string serialization */

std::string DataSerializer<std::string>::operator()(const char *key, const char *value) const
{
    return value;
}


bool DataSerializer<std::string>::operator()(const char *key, const char *value, std::string &result) const
{
    result = value;
    return true;
}


std::string DataSerializer<std::string>::operator()(const std::string &value) const
{
    return value;
}



}
