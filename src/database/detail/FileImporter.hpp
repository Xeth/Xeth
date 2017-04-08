#pragma once 

#include <string>

#include <json/value.h>
#include <boost/filesystem.hpp>

#include "io/JsonReader.hpp"
#include "../KeyAttributesReader.hpp"


namespace Xeth{


class NullValidatorArgs
{};

class NullValidator
{
    public:
        template<class Item>
        bool operator()(const Item &) const;

        template<class Item>
        bool operator()(const Item &, const NullValidatorArgs &) const;
};



template<class FileStore, class Validator=NullValidator>
class FileImporter
{
    public:
        typedef FileStore Store;
        typedef typename Store::Data Data;
        typedef typename Store::DataSerializer DataSerializer;

    public:

        FileImporter(Store &);
        FileImporter(Store &, const Validator &);

        bool import(const std::string &);
        bool import(const std::string &, Json::Value &result);
        bool import(const std::string &, Data &result);
        bool import(const std::string &, Json::Value &, Data &);


        template<class ValidatorArgs>
        bool import(const std::string &, const ValidatorArgs &);

        template<class ValidatorArgs>
        bool import(const std::string &, Json::Value &result, const ValidatorArgs &);

        template<class ValidatorArgs>
        bool import(const std::string &, Data &result, const ValidatorArgs &);

        template<class ValidatorArgs>
        bool import(const std::string &, Json::Value &, Data &, const ValidatorArgs &);


    private:
        Store &_store;
        Validator _validator;

};



}

#include "FileImporter.ipp"
