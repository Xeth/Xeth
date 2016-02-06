#include "ScanIndexStore.hpp"

namespace Xeth{



ScanIndexStore::ScanIndexStore(const char *path) : Base(path)
{}

ScanIndexStore::ScanIndexStore(const std::string &path) : Base(path)
{}

ScanIndexStore::ScanIndexStore()
{}


bool ScanIndexStore::insert(const char *key, size_t index)
{
    return replace(key, index);
}

size_t ScanIndexStore::get(const char *key) const
{
    size_t result = 0;
    Base::get(key, result);
    return result;
}

}
