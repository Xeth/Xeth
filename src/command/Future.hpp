#pragma once

#include <QFutureWatcher>
#include <QFuture>
#include <QObject>

#include <boost/shared_ptr.hpp>


namespace Xeth{



class Future : public QObject
{
    Q_OBJECT
    public:
        Future();
        Future(const QFuture<QVariant> &);
        Future(const Future &);
        ~Future();
        Future & operator = (const Future &);

    public:
        Q_INVOKABLE QVariant getResult();
        Q_INVOKABLE bool isFinished();
        Q_INVOKABLE bool isRunning();
        Q_INVOKABLE bool isEmpty();

        Q_INVOKABLE void dispose();
        Q_INVOKABLE void wait();

    signals:
        void Finished(const QVariant &);

    private slots:
        void emitDone();

    private:
        boost::shared_ptr<QFutureWatcher<QVariant> > _watcher;
};



}


Q_DECLARE_METATYPE(Xeth::Future);
