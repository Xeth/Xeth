#pragma once

#include <QTimer>
#include <QProcess>
#include <QString>
#include <QStringList>

#include "env/Settings.hpp"


namespace Xeth{



class ProcessSupervisor : public QObject
{
    Q_OBJECT

    public:

        ProcessSupervisor(const Settings &);
        ProcessSupervisor();
        ~ProcessSupervisor();

        void supervise(QProcess *);
        void stop();
        void start();

        void setRespawnLimit(size_t );
        bool isActive() const;

        void moveToThread(QThread *);

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


    private:
        size_t _respawnLimit;
        size_t _respawnCnt;
        size_t _respawnInterval;
        QTimer _timer;
        QProcess *_process;
};


}
