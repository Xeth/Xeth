#pragma once 

#include <QObject>

#include "command/filesystem/BrowseCommand.hpp"
#include "command/filesystem/SaveImageCommand.hpp"
#include "command/filesystem/ReadImageCommand.hpp"
#include "command/Invoker.hpp"

#include "Notifier.hpp"



namespace Xeth{


class FileSystemFacade : public QObject
{
    Q_OBJECT
    public:
        FileSystemFacade(Invoker<Notifier> &);


        Q_INVOKABLE QVariant browse(const QVariantMap &);
        Q_INVOKABLE QVariant browse();
        Q_INVOKABLE QVariant readImage(const QString &);

    private:
        Invoker<Notifier> &_invoker;
};


}
