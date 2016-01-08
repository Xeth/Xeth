
#include "ScanCriterion.hpp"

namespace Xeth{

ScanCriterion::ScanCriterion(const char *address) :
    _address(address)
{}


ScanCriterion::~ScanCriterion()
{}

const char * ScanCriterion::getAddress() const
{
    return _address.c_str();
}

void ScanCriterion::processHeader
(
    size_t,
    const std::string &,
    const std::string &,
    const BigInt &,
    time_t ,
    QJsonArray &
)
{}

void ScanCriterion::processTransaction
(
    const std::string &,
    const std::string &,
    const std::string &,
    const BigInt &,
    const std::string &,
    time_t ,
    QJsonArray &
)
{}

}
