
#include <QObject>
#include <QTest>

#include <sstream>

#include "synchronizer/ChainProgress.hpp"

#include "simulator/BlockChainSimulator.hpp"


class BlockChainProgressTest : public QObject
{
    Q_OBJECT

    private slots:
        void testZeroProgress();
        void testPartialProgress();
        void testProgressComplete();
        void testProgressUpdate();

    private:
        std::string makeBlock(time_t);
};
