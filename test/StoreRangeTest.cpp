#include "StoreRangeTest.hpp"


StoreRangeTest::Store StoreRangeTest::makeStore()
{
    Store store;
    for(int i=0; i<100; i++)
    {
        store.insert(i);
    }
    return store;
}

void StoreRangeTest::testLimit()
{
    Store store = makeStore();

    StoreRange range(store);

    range.setLimit(10);

    int value = 0;
    for(StoreRange::Iterator it=range.begin(), end=range.end(); it!=end; ++it)
    {
        QCOMPARE(*it, value++);
    }

    QCOMPARE(value, 10);

}


void StoreRangeTest::testOffset()
{
    Store store = makeStore();

    StoreRange range(store);

    range.setLimit(10);
    range.setOffset(10);

    int value = 10;
    for(StoreRange::Iterator it=range.begin(), end=range.end(); it!=end; ++it)
    {
        QCOMPARE(*it, value++);
    }

    QCOMPARE(value, 20);

}


void StoreRangeTest::testLimitOverflow()
{
    Store store = makeStore();

    StoreRange range(store);
    range.setLimit(10);
    range.setOffset(95);

    int value = 95;
    for(StoreRange::Iterator it=range.begin(), end=range.end(); it!=end; ++it)
    {
        QCOMPARE(*it, value++);
    }

    QCOMPARE(value, 100);
}


void StoreRangeTest::testOffsetOverflow()
{
    Store store = makeStore();

    StoreRange range(store);
    range.setLimit(10);
    range.setOffset(101);

    int value = 101;
    for(StoreRange::Iterator it=range.begin(), end=range.end(); it!=end; ++it)
    {
        QCOMPARE(*it, value++);
    }

    QCOMPARE(value, 101);
}
