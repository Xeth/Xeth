#pragma once

#include <QTimer>

#include "EthProcess.hpp"


namespace Xeth{



class EthProcessSupervisor : public QObject
{
    Q_OBJECT

    public:

        EthProcessSupervisor(const Settings &);
        EthProcessSupervisor();
        ~EthProcessSupervisor();

        void start();
        void stop();

        void setRespawnLimit(size_t );

        bool isActive() const;

        void moveToThread(QThread *);

    signals:
        void Error(const QString &);
        void Ready();

    private:
        void initSignals();

    private slots:
        void fork();
        void scheduleFork();
        void handleError(QProcess::ProcessError error);
        void handleReady();


    private:
        size_t _respawnLimit;
        size_t _respawnCnt;
        size_t _respawnInterval;
        QTimer _timer;
        EthProcess _process;
};


}
