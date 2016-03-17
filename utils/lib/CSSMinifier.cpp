#include "CSSMinifier.hpp"

QString MinifyCSS::operator()(const QString &content)
{
    QString result = content;
    result.remove(QRegExp("/\\*([^*]|[\r\n]|(\\*+([^*/]|[\r\n])))*\\*+/"));
    return result.simplified();
}
