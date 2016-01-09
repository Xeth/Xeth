#include "ConfigStore.hpp"

namespace Xeth{


std::string ConfigStoreDataEncoder::operator ()(const char *, const char *value)
{
    return value;
}


bool ConfigStoreDataEncoder::operator ()(const char *, const char *value, std::string &result)
{
    result = value;
    return true;
}


std::string ConfigStoreDataEncoder::operator ()(const std::string &data)
{
    return data;
}


}
