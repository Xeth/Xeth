#include "RandomString.hpp"


std::string RandomHexString(size_t length)
{
    static std::string alphabet = "0123456789abcdef"; 
    static boost::random::uniform_int_distribution<> dist(0, alphabet.size() - 1);

    boost::random::random_device rng;
    std::string result;
    result.resize(length);

    for(size_t i = 0; i < length; ++i)
    {
        result[i] = result[dist(rng)];
    }

    return result;
}


std::string RandomHexString()
{
    return RandomHexString(65);
}



