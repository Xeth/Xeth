#pragma once 


#include <QFileDialog>
#include <QVariant>
#include <QVariantMap>

namespace Xeth{


class BrowseCommand
{
    public:
        QVariant operator()();
        QVariant operator()(const QVariantMap &);

    private:
        QVariant browseFile(const QString &caption, QString &extensions);
        QVariant browseNewFile(const QString &caption);
        QVariant browseDirectory(const QString &caption);
};


}
