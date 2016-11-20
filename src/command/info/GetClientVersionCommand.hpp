#pragma once

#include <QString>
#include <QRegExp>
#include <QStringList>
#include <QProcess>

#include "conf/Settings.hpp"
#include "process/EthProcessFactory.hpp"


namespace Xeth{


class GetClientVersionCommand
{
    public:
        typedef enum
        {
            Full_Text,
            Version_Only
        } Format;

    public:
        GetClientVersionCommand(const Settings &);
        QString operator()(Format format=Full_Text) const;

    private:
        bool isParity(QProcess *) const;
        QString getParityVersion(QProcess *, Format) const;
        QString getGethVersion(QProcess *, Format) const;
        QString getClientVersion(QProcess *, const QString &, const QString &, const QString &) const;
        QString getGethVersion(QProcess *, const QString &) const;
        QString getParityVersion(QProcess *, const QString &) const;

    private:
        const Settings &_settings;
};


}
