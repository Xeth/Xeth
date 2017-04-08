#include <QDebug>
namespace Xeth{

template<class Store, class Validator>
FileImporter<Store, Validator>::FileImporter(Store &store) :
    _store(store)
{}


template<class Store, class Validator>
FileImporter<Store, Validator>::FileImporter(Store &store, const Validator &validator) :
    _store(store),
    _validator(validator)
{}


template<class Store, class Validator>
bool FileImporter<Store, Validator>::import(const std::string &path)
{
    return import(path, NullValidatorArgs());
}

template<class Store, class Validator>
bool FileImporter<Store, Validator>::import(const std::string &path, Json::Value &result)
{
    return import(path, result, NullValidatorArgs());
}

template<class Store, class Validator>
bool FileImporter<Store, Validator>::import(const std::string &path, Data &result)
{
    return import(path, result, NullValidatorArgs());
}


template<class Store, class Validator>
bool FileImporter<Store, Validator>::import(const std::string &path, Json::Value &json, Data &value)
{
    return import(path, json, value, NullValidatorArgs());
}


/////


template<class Store, class Validator>
template<class ValidatorArgs>
bool FileImporter<Store, Validator>::import(const std::string &path, const ValidatorArgs &args)
{
    Json::Value json;
    Data val;
    return import(path, json, val, args);
}

template<class Store, class Validator>
template<class ValidatorArgs>
bool FileImporter<Store, Validator>::import(const std::string &path, Json::Value &result, const ValidatorArgs &args)
{
    Data value;
    return import(path, result, value, args);
}

template<class Store, class Validator>
template<class ValidatorArgs>
bool FileImporter<Store, Validator>::import(const std::string &path, Data &result, const ValidatorArgs &args)
{
    Json::Value json;
    return import(path, json, result, args);
}


template<class Store, class Validator>
template<class ValidatorArgs>
bool FileImporter<Store, Validator>::import(const std::string &path, Json::Value &json, Data &value, const ValidatorArgs &args)
{
    JsonReader reader;

    std::string absolutePath = boost::filesystem::absolute(path).string();
    if(!reader.read(absolutePath.c_str(), json))
    {
        qDebug()<<"~~~~~~~~~~~~~~~~~~~~~~~~ invalid file path";
        return false;
    }

    //validate content
    try
    {
        DataSerializer serializer;
        value = serializer.unserialize(json);
        if(!_validator(value, args))
        {
            qDebug()<<"~~~~~~~~~~~~~~~~~~~~~~~` failed to validate";
            return false;
        }
        KeyAttributesReader<Store> attrs(path, json);
        
        return _store.replace(value, attrs.getCreationTime());
    }
    catch(...)
    {}
    qDebug()<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~` got exception ";
    return false;
}





template<class Item>
bool NullValidator::operator()(const Item &) const
{
    return true;
}


template<class Item>
bool NullValidator::operator()(const Item &, const NullValidatorArgs &) const
{
    return true;
}





}
