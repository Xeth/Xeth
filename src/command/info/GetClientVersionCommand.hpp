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
        GetClientVersionCommand(const Settings &);
        QString operator()() const;

    private:
        bool isParity(QProcess *) const;
        QString getParityVersion(QProcess *) const;
        QString getGethVersion(QProcess *) const;
        QString getClientVersion(QProcess *, const QString &, const QString &, const QString &) const;

    private:
        const Settings &_settings;
};


}
