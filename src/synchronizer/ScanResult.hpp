#pragma once 

#include <utility>
#include <QJsonArray>
#include <QMetaType>

namespace Xeth{


struct ScanResult
{
    QJsonArray transactions;
    QJsonArray stealthPayments;
    size_t lastBlock;
};


struct PartialScanResult
{
    typedef std::pair<QJsonArray::const_iterator, QJsonArray::const_iterator> QJsonArrayRange;

    QJsonArrayRange transactions;
    QJsonArrayRange stealthPayments;

    size_t lastBlock;
};


PartialScanResult MakePartialScanResult
(
    QJsonArray::const_iterator tBegin,
    QJsonArray::const_iterator tEnd,
    QJsonArray::const_iterator sBegin,
    QJsonArray::const_iterator sEnd,
    size_t
);

PartialScanResult MakePartialScanResult(const ScanResult &, size_t txCount, size_t stCount, size_t blockIndex);


}

Q_DECLARE_METATYPE(Xeth::PartialScanResult)

