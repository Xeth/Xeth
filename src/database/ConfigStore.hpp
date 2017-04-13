#pragma once 

#include <QObject>
#include <QString>
#include "detail/LevelDbStore.hpp"
#include "conf/SettingSource.hpp"


namespace Xeth {


class ConfigStore : 
    public QObject,
    public SettingSource,
    public LevelDbStore<QString>
{
    Q_OBJECT
    public:
        typedef LevelDbStore<QString> Base;

    public:
        ConfigStore();
        ConfigStore(const char *path);
        ConfigStore(const std::string &);
        ConfigStore(const boost::filesystem::path &path);

        void insert(const QString &, const QString &);
        void insert(const char *, const QString &);

        bool has(const char *) const;
        QString get(const char *) const;

    signals:
        void Change(const QString &, const QString &);
};

}
