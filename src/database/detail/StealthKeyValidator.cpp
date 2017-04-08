#include "StealthKeyValidator.hpp"


namespace Xeth{



void StealthKeyUnlocker::operator()(StealthKey &key, const std::string &password) const
{
    key.getSpendPrivateKeys()[0].unlock(password);
}



}
