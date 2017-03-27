#include "XmlReader.hpp"
#include <QTextStream>
#include <QDebug>

XmlReader::XmlReader()
{}


XmlReader::XmlReader(const QString &path)
{
    if(!open(path))
    {
        throw std::runtime_error("failed to open XML file");
    }
}


bool XmlReader::open(const QString &path)
{
    int errorColumn, errorLine;
    QString errorMsg;

    QFile file(path);
    QDomDocument document;

    if (!document.setContent(&file, &errorMsg, &errorLine, &errorColumn))
    {
        QString error("Syntax error line %1, column %2:\n%3");
        error = error
                .arg(errorLine)
                .arg(errorColumn)
                .arg(errorMsg);
        qDebug()<<error;
        return false;
    }
    _root = document.firstChild().toElement();
    return true;
}


const QDomElement & XmlReader::getRoot() const
{
    return _root;
}


QDomElement XmlReader::findByAttribute(const QString &key, const QString &value) const
{
    return findByAttribute(_root.firstChildElement(), key, value);
}


QDomElement XmlReader::findByAttribute(const QDomElement &node, const QString &key, const QString &value) const
{
    QDomNamedNodeMap attrs = node.attributes();
    if(attrs.contains(key) && attrs.namedItem(key).nodeValue() == value)
    {
        return node;
    }
    else
    {
        QDomElement nextNode = node.nextSiblingElement();
        if(node.isNull())
        {
            return node;
        }
        return findByAttribute(nextNode, key, value);
    }

}


QDomElement XmlReader::findByTagName(const QString &name) const
{
    return _root.elementsByTagName(name).at(0).toElement();
}




