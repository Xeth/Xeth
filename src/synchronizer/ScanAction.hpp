#pragma once

#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>

#include <QObject>
#include <QJsonArray>

#include "ScanCriteria.hpp"
#include "ScanProgress.hpp"

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

        const QJsonArray & getResult() const;
        size_t getScanHeight() const;

    private:
        void execute(BlockChain &, ScanCriteria &, ScanProgress &);
        void execute(BlockChain &, ScanCriteria &);

    signals:
        void Done();

    private:
        boost::shared_ptr<boost::thread> _thread;
        QJsonArray _result;
        size_t _scanHeight;
};


}
