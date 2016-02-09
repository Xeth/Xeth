#pragma once 

#include <string>

#include <boost/regex.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>
#include <sstream>

#include "io/JsonReader.hpp"

#include "StealthKeyStore.hpp"
#include "EthereumKeyStore.hpp"

namespace Xeth{

namespace detail{

template<class Store>
class KeyAttributesReader
{};

}


template<class Store>
class KeyAttributesReader : public detail::KeyAttributesReader<Store>
{
    public:
        typedef detail::KeyAttributesReader<Store> Base;

    public:
        KeyAttributesReader(const std::string &name);
        KeyAttributesReader(const std::string &name, const Json::Value &);
};


namespace detail{

template<>
class KeyAttributesReader<StealthKeyStore>
{
    public:
        KeyAttributesReader(const std::string &name);
        KeyAttributesReader(const std::string &name, const Json::Value &json);

        time_t getCreationTime() const;
        std::string getAddress() const;

    private:
        std::string _path;
        Json::Value _json;
};


template<>
class KeyAttributesReader<EthereumKeyStore>
{
    public:
        KeyAttributesReader(const std::string &name);
        KeyAttributesReader(const std::string &name, const Json::Value &);

        time_t getCreationTime() const;
        std::string getAddress() const;

    private:
        void throwIfNotExists();

    private:
        std::string _path; //can get attributes only from filename
};


}

}

#include "KeyAttributesReader.ipp"
