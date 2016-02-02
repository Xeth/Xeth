#pragma once

#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>

#include <QObject>
#include <QJsonArray>

#include "ScanCriteria.hpp"
#include "ScanProgress.hpp"
#include "ScanResult.hpp"

namespace Xeth{


class ScanAction : public QObject
{
    Q_OBJECT
    public:
        ScanAction();

        void start(BlockChain &, ScanCriteria &, ScanProgress &);
        void start(BlockChain &, ScanCriteria &);

        void stop();
        void waitToComplete();
        bool isActive() const;

        const ScanResult & getResult() const;

    private:
        void execute(BlockChain &, ScanCriteria &, ScanProgress &);
        void execute(BlockChain &, ScanCriteria &);

    signals:
        void Done();

    private:
        boost::shared_ptr<boost::thread> _thread;
        ScanResult _result;
};


}
