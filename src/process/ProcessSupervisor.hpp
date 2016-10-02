#pragma once

#include <QTimer>
#include <QProcess>
#include <QMutex>
#include <QMutexLocker>
#include <QString>
#include <QStringList>
#include <QAtomicInt>
#include <boost/signals2.hpp>

#include "conf/Settings.hpp"


namespace Xeth{



class ProcessSupervisor : public QObject
{
    Q_OBJECT

    public:

        ProcessSupervisor(const Settings &);
        ProcessSupervisor();
        ~ProcessSupervisor();

        void attach(QProcess *);
        void stop();
        void start();
        void restart();

        void setRespawnLimit(size_t );
        bool isActive() const;

        void moveToThread(QThread *);
        QString getProgram() const;

        template<class Loader>
        void addLoader(const Loader &);

    signals:
        void Error(const QString &);

    private:
        void initSignals();
        void watch(QProcess *);
        void stopListening();

    private slots:
        void fork();
        void scheduleFork();
        void handleError(QProcess::ProcessError error);
        void forkAndInitialize();


    private:
        size_t _respawnLimit;
        size_t _respawnCnt;
        size_t _respawnInterval;
        QTimer _timer;
        QProcess *_process;
        QMutex _mutex;
        time_t _lastStart;
        boost::signals2::signal<void()> _loaders;
};


}
#include "ProcessSupervisor.ipp"
