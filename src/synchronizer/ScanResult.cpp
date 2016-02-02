#include "ScanResult.hpp"

namespace Xeth{


PartialScanResult MakePartialScanResult
(
    QJsonArray::const_iterator tBegin,
    QJsonArray::const_iterator tEnd,
    QJsonArray::const_iterator sBegin,
    QJsonArray::const_iterator sEnd,
    size_t lastBlock
)
{
    PartialScanResult result;
    result.transactions = std::make_pair(tBegin, tEnd);
    result.stealthPayments = std::make_pair(sBegin, sEnd);
    result.lastBlock = lastBlock;
    return result;
}


PartialScanResult MakePartialScanResult(const ScanResult &result, size_t txCount, size_t stCount, size_t blockIndex)
{
    QJsonArray::const_iterator txEnd = result.transactions.constEnd();
    QJsonArray::const_iterator stEnd = result.stealthPayments.constEnd();
    PartialScanResult partial;
    partial.transactions = std::make_pair(txEnd - txCount, txEnd);
    partial.stealthPayments = std::make_pair(stEnd - stCount, stEnd);
    partial.lastBlock = blockIndex;
    return partial;
}


}
