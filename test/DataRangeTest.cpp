#include "DataRangeTest.hpp"


DataRangeTest::Store DataRangeTest::makeStore()
{
    Store store;
    for(int i=0; i<100; i++)
    {
        store.insert(i);
    }
    return store;
}

void DataRangeTest::testLimit()
{
    Store store = makeStore();

    DataRange range(store);

    range.setLimit(10);

    int value = 0;
    for(DataRange::Iterator it=range.begin(), end=range.end(); it!=end; ++it)
    {
        QCOMPARE(*it, value++);
    }

    QCOMPARE(value, 10);

}


void DataRangeTest::testOffset()
{
    Store store = makeStore();

    DataRange range(store);

    range.setLimit(10);
    range.setOffset(10);

    int value = 10;
    for(DataRange::Iterator it=range.begin(), end=range.end(); it!=end; ++it)
    {
        QCOMPARE(*it, value++);
    }

    QCOMPARE(value, 20);

}


void DataRangeTest::testLimitOverflow()
{
    Store store = makeStore();

    DataRange range(store);
    range.setLimit(10);
    range.setOffset(95);

    int value = 95;
    for(DataRange::Iterator it=range.begin(), end=range.end(); it!=end; ++it)
    {
        QCOMPARE(*it, value++);
    }

    QCOMPARE(value, 100);
}


void DataRangeTest::testOffsetOverflow()
{
    Store store = makeStore();

    DataRange range(store);
    range.setLimit(10);
    range.setOffset(101);

    int value = 101;
    for(DataRange::Iterator it=range.begin(), end=range.end(); it!=end; ++it)
    {
        QCOMPARE(*it, value++);
    }

    QCOMPARE(value, 101);
}
