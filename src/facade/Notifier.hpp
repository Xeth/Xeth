#pragma once

#include <QObject>
#include <QString>

namespace Xeth{


class Notifier : public QObject
{
    Q_OBJECT
    public:

        void emitError(const QString &);
        void emitMessage(const QString &);
        void emitReady();

    signals:
        void Error(const QString &);
        void Message(const QString &);
        void Ready();
};


}
