#include "ScanActionTest.hpp"

#if __GETH_SIMULATOR_ENABLED__

ScanActionTest::ScanActionTest() :
    _context(true)
{}

void ScanActionTest::testStart()
{
    BlockChain chain(_context.getProvider());
    Xeth::ScanCriteria criteria;
    Xeth::ScanAction action;
    Xeth::ScanProgress progress;
    _context.getBlockChain().setHeight(999999999999);
    criteria.addCriterion<Xeth::AccountScanCriterion>(10, "asdasd123");

    action.start(chain, criteria, progress);

    QVERIFY(action.isActive());
    boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
    QVERIFY(_context.getBlockChain().getTotalFetched() > 0);
    action.stop();
}


void ScanActionTest::testStop()
{
    BlockChain chain(_context.getProvider());
    Xeth::ScanCriteria criteria;
    Xeth::ScanAction action;
    Xeth::ScanProgress progress;
    _context.getBlockChain().setHeight(999999999999);

    criteria.addCriterion<Xeth::AccountScanCriterion>(10, "asdasd123");

    action.start(chain, criteria, progress);

    QVERIFY(action.isActive());
    action.stop();
    size_t fetched = _context.getBlockChain().getTotalFetched();
    QVERIFY(fetched > 0);
    boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
    QVERIFY(fetched == _context.getBlockChain().getTotalFetched());
}


void ScanActionTest::testResume()
{
    BlockChain chain(_context.getProvider());
    Xeth::ScanCriteria criteria;
    Xeth::ScanAction action;
    Xeth::ScanProgress progress;
    _context.getBlockChain().setHeight(99999999999999);

    criteria.addCriterion<Xeth::AccountScanCriterion>(10, "asdasd123");

    action.start(chain, criteria, progress);

    QVERIFY(action.isActive());
    action.stop();
    size_t fetched = _context.getBlockChain().getTotalFetched();
    QVERIFY(fetched > 0);
    action.start(chain, criteria, progress);
    boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
    QVERIFY(fetched < _context.getBlockChain().getTotalFetched());
    action.stop();
}

void ScanActionTest::testComplete()
{
    BlockChain chain(_context.getProvider());
    Xeth::ScanCriteria criteria;
    Xeth::ScanAction action;
    Xeth::ScanProgress progress;
    _context.getBlockChain().setHeight(5);
    _context.getBlockChain().resetCounter();

    criteria.addCriterion<Xeth::AccountScanCriterion>(0, "asdasd123");
    action.start(chain, criteria, progress);

    boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
    QVERIFY(!action.isActive());
    QVERIFY(_context.getBlockChain().getTotalFetched()==6);
}

#endif
