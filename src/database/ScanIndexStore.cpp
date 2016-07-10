#include "ScanIndexStore.hpp"

namespace Xeth{



ScanIndexStore::ScanIndexStore(const char *path) : Base(path)
{}


ScanIndexStore::ScanIndexStore(const std::string &path) : Base(path)
{}


ScanIndexStore::ScanIndexStore(const boost::filesystem::path &path) : Base(path)
{}


ScanIndexStore::ScanIndexStore()
{}


bool ScanIndexStore::insert(const char *key, size_t index)
{
    HexAddressNormalizer normalizer;
    return replace(normalizer(key).c_str(), index);
}

size_t ScanIndexStore::get(const char *key) const
{
    size_t result = 0;
    HexAddressNormalizer normalizer;
    Base::get(normalizer(key).c_str(), result);
    return result;
}

}
