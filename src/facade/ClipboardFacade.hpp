#pragma once 

#include <QObject>
#include <QVariant>
#include <QVariantMap>
#include <QString>


#include "command/clipboard/CopyToClipboardCommand.hpp"
#include "command/clipboard/GetFromClipboardCommand.hpp"
#include "command/Invoker.hpp"

#include "Notifier.hpp"



namespace Xeth{


class ClipboardFacade : public QObject
{
    Q_OBJECT

    public:

        ClipboardFacade(Invoker<Notifier> &);

        Q_INVOKABLE QVariant getText();
        Q_INVOKABLE QVariant setText(const QString &);

    private:
        Invoker<Notifier> &_invoker;
};


}
