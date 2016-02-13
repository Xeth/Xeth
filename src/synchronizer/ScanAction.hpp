#pragma once

#include <boost/shared_ptr.hpp>

#include <QObject>
#include <QJsonArray>

#include "ScanCriteria.hpp"
#include "ScanProgress.hpp"
#include "ScanResult.hpp"
#include "detail/ScanWorker.hpp"

namespace Xeth{




class ScanAction : public QObject
{
    Q_OBJECT
    public:
        ScanAction();

        void start(BlockChain &, ScanCriteria &, ScanProgress &);

        void stop();
        void waitToComplete();
        bool isActive() const;

        const ScanResult & getResult() const;

    signals:
        void Done();

    private:
        void emitDone();

    private:
        boost::shared_ptr<QThread> _worker;
        ScanResult _result;
};


}

