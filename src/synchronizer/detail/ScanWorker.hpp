#pragma once 

#include <QThread>

#include "ethrpc/BlockChain.hpp"
#include "../ScanCriteria.hpp"
#include "../ScanProgress.hpp"


namespace Xeth{


class ScanWorker : public QThread
{
    Q_OBJECT

    public:
        typedef Ethereum::Connector::BlockChain BlockChain;

    public:
        ScanWorker(QThread *parent, BlockChain &, ScanCriteria &, ScanResult &, ScanProgress &);
        void run();

        void stop();
        bool isInterrupted() const;

    private:
        QThread *_parent;
        bool _interrupted;
        BlockChain &_chain;
        ScanCriteria &_criteria;
        ScanResult &_result;
        ScanProgress &_progress;
};



}
