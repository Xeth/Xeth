#include "ScanProgressTest.hpp"

#include <QDebug>

void ScanProgressTest::testStep()
{
    Xeth::ScanProgress progress;
    progress.setRange(0, 10);

    progress.next();

    QCOMPARE(progress.getValue(), 10.0);
}

void ScanProgressTest::testComplete()
{
    Xeth::ScanProgress progress;
    progress.setRange(0, 9);
    for(int i=0; i<9; i++)
    {
        progress.next();
    }
    QCOMPARE(progress.getValue(), 100.0);
}

void ScanProgressTest::testReuse()
{
    Xeth::ScanProgress progress;
    progress.setRange(0, 9);
    for(int i=0; i<9; i++)
    {
        progress.next();
    }
    QCOMPARE(progress.getValue(), 100.0);

    progress.setRange(9, 200);
    QCOMPARE(progress.getValue(), 4.5);

}

void ScanProgressTest::testOverflow()
{
    Xeth::ScanProgress progress;
    progress.setRange(0, 9);
    for(int i=0; i<15; i++)
    {
        progress.next();
    }
    QCOMPARE(progress.getValue(), 100.0);
}

void ScanProgressTest::testSignal()
{
    Xeth::ScanProgress progress;
    progress.setRange(0, 10);

    QSignalSpy spy(&progress, SIGNAL(Progress(double)));

    progress.next();

    QCOMPARE(spy.at(0).at(0).toDouble(), 10.0);
}

void ScanProgressTest::testCompleteSignal()
{
    Xeth::ScanProgress progress;
    progress.setRange(0, 10);
    progress.setSignalStep(45);
    QSignalSpy spy(&progress, SIGNAL(Progress(double)));

    for(int i=0; i<10; i++)
    {
        progress.next();
    }

    QCOMPARE(spy.size(), 3);

    QCOMPARE(spy.at(0).at(0).toDouble(), 50.0);
    QCOMPARE(spy.at(1).at(0).toDouble(), 90.0);
    QCOMPARE(spy.at(2).at(0).toDouble(), 100.0);
}


