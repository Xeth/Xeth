#include "ScanIndexStore.hpp"

namespace Xeth{

size_t ScanIndexDataDecoder::operator ()(const char *key, const char *value) const
{
    size_t result = 0;
    operator ()(key, value, result);
    return result;
}

bool ScanIndexDataDecoder::operator ()(const char *, const char *value, size_t &result) const
{
    result = boost::lexical_cast<size_t>(value);
    return true;
}

std::string ScanIndexDataDecoder::operator ()(size_t data) const
{
    return boost::lexical_cast<std::string>(data);
}

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

size_t ScanIndexStore::get(const char *key)
{
    size_t result = 0;
    Base::get(key, result);
    return result;
}

}
