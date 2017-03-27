#pragma once

#include <QFile>
#include <QDomDocument>
#include <QDomElement>
#include <QDebug>



class XmlReader
{
    public:
        XmlReader();
        XmlReader(const QString &);

        bool open(const QString &);

        QDomElement findByAttribute(const QString &name, const QString &value) const;
        QDomElement findByTagName(const QString &name) const;
        const QDomElement  & getRoot() const;

    private:
        QDomElement findByAttribute(const QDomElement &node, const QString &key, const QString &value) const;

    private:
        QDomElement _root;
};
