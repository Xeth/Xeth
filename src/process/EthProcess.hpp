#pragma once

#include <QProcess>
#include <QString>
#include <QStringList>

#include "env/Settings.hpp"


namespace Xeth{


class EthProcess : public QProcess
{
    public:
        EthProcess();
        EthProcess(const Settings &);

        ~EthProcess();

        void exec();
        void exec(const QStringList &args);

    private:
        using QProcess::start;

    private:
        QString _command;
        QStringList _args;
};


}
