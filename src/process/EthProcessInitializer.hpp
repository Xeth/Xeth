#pragma once

#include <QProcess>
#include <QString>
#include <QStringList>
#include <QApplication>
#include <QFileInfo>

#include "conf/Settings.hpp"
#include "io/ApplicationPath.hpp"


namespace Xeth{


class EthProcessInitializer
{
    public:
        static void Initialize(QProcess &);
        static void Initialize(QProcess &, const Settings &);
        static void Initialize(QProcess &, const Settings &, const QStringList &args);

        static QString GetCommand(const Settings &);
        static QString GetDefaultCommand();
        static QStringList GetArguments(const QString &, const Settings &);
        static QStringList GetGethArguments(const Settings &);
        static QStringList GetParityArguments(const Settings &);

    private:
        static QString GetVendorPath(const char *name);
        static QString GetLocalVendorPath(const char *name);
        static QString GetVendorPath(const QString &root, const char *name);
        static bool FileExists(const QString &path);
        static void SetEnvironment(QProcess &process);
        static QString GetDefaultKeystorePath();
        static QString GetParityKeystorePath(const Settings &);
        static QString GetGethKeystorePath(const Settings &);
        static void SetArgument(QStringList &, const char *, const QString &);

        static void SetPathArgument(QStringList &, const Settings &);

};


}
