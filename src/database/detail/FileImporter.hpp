#pragma once 

#include <string>

#include <json/value.h>
#include <boost/filesystem.hpp>

#include "io/JsonReader.hpp"


namespace Xeth{


template<class Store>
class FileImporter
{
    public:
        typedef typename Store::Data Data;
        typedef typename Store::DataSerializer DataSerializer;

    public:

        FileImporter(Store &);

        bool import(const std::string &);
        bool import(const std::string &, Json::Value &result);
        bool import(const std::string &, Data &result);
        bool import(const std::string &, Json::Value &, Data &);

    private:
        Store &_store;

};



}

#include "FileImporter.ipp"
