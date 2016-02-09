namespace Xeth{

template<class Store>
FileImporter<Store>::FileImporter(Store &store) :
    _store(store)
{}


template<class Store>
bool FileImporter<Store>::import(const std::string &path)
{
    Json::Value json;
    Data val;
    return import(path, json, val);
}

template<class Store>
bool FileImporter<Store>::import(const std::string &path, Json::Value &result)
{
    Data value;
    return import(path, result, value);
}

template<class Store>
bool FileImporter<Store>::import(const std::string &path, Data &result)
{
    Json::Value json;
    return import(path, json, result);
}


template<class Store>
bool FileImporter<Store>::import(const std::string &path, Json::Value &json, Data &value)
{
    JsonReader reader;

    boost::filesystem::path source = boost::filesystem::absolute(path);
    if(!reader.read(source.string().c_str(), json))
    {
        return false;
    }

    //validate content
    try
    {
        DataSerializer serializer;
        value = serializer.unserialize(json);
        return _store.insert(source.filename().string(), value);
    }
    catch(...)
    {}
    return false;
}






}
