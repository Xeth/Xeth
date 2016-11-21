#pragma once

#include <QVariant>
#include <QFileInfo>
#include <QString>
#include <QFile>
#include <QCoreApplication>

#include "process/ProcessSupervisor.hpp"



namespace Xeth{


class UpdateEthereumClientCommand
{
    public:
        UpdateEthereumClientCommand(ProcessSupervisor &);
        QVariant operator()(const QString &);

    private:
        void backupIfExists(const QString &, const QString &);
        QString makeBinPath(const QString &, const QFileInfo &);
        QString getVendorsPath();

    private:
        ProcessSupervisor &_client;
};


}
