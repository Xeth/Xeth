#include "ScanActionTest.hpp"


void ScanActionTest::testStart()
{
    Xeth::ScanCriteria criteria;
    Xeth::ScanAction action;
    Xeth::ScanProgress progress;
    RandomBlockChain chain(99999999999999);

    criteria.addCriterion<Xeth::AccountScanCriterion>(10, "asdasd123");

    action.start(chain, criteria, progress);

    QVERIFY(action.isActive());
    sleep(1);
    QVERIFY(chain.getTotalFetched() > 0);
    action.stop();
}


void ScanActionTest::testStop()
{
    Xeth::ScanCriteria criteria;
    Xeth::ScanAction action;
    Xeth::ScanProgress progress;
    RandomBlockChain chain(99999999999999);

    criteria.addCriterion<Xeth::AccountScanCriterion>(10, "asdasd123");

    action.start(chain, criteria, progress);

    QVERIFY(action.isActive());
    action.stop();
    size_t fetched = chain.getTotalFetched();
    QVERIFY(fetched > 0);
    sleep(1);
    QVERIFY(fetched == chain.getTotalFetched());
}


void ScanActionTest::testResume()
{
    Xeth::ScanCriteria criteria;
    Xeth::ScanAction action;
    Xeth::ScanProgress progress;
    RandomBlockChain chain(99999999999999);

    criteria.addCriterion<Xeth::AccountScanCriterion>(10, "asdasd123");

    action.start(chain, criteria, progress);

    QVERIFY(action.isActive());
    action.stop();
    size_t fetched = chain.getTotalFetched();
    QVERIFY(fetched > 0);
    action.start(chain, criteria, progress);
    sleep(1);
    QVERIFY(fetched < chain.getTotalFetched());
    action.stop();
}

void ScanActionTest::testComplete()
{
    Xeth::ScanCriteria criteria;
    Xeth::ScanAction action;
    Xeth::ScanProgress progress;
    RandomBlockChain chain(5);

    criteria.addCriterion<Xeth::AccountScanCriterion>(0, "asdasd123");
    action.start(chain, criteria, progress);

    sleep(1);
    QVERIFY(!action.isActive());
    QVERIFY(chain.getTotalFetched()==6);
}
