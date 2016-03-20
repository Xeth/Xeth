namespace Xeth{



template<class T>
T Settings::get(const char *name) const
{
    return boost::lexical_cast<T>(get(name));
}


template<class T>
T Settings::get(const char *name, const T &defaultVal) const throw()
{
    boost::unordered_map<std::string, std::string>::const_iterator it= _data.find(name);
    if(it==_data.end())
    {
        return defaultVal;
    }
    return boost::lexical_cast<T>(it->second);
}



template<class T, class Vector>
void Settings::getVector(const char *name, Vector &vec) const
{
    std::vector<std::string> items;
    getVector(name, items);
    for(std::vector<std::string>::iterator it=items.begin(), end=items.end(); it!=end; ++it)
    {
        vec.push_back(boost::lexical_cast<T>(*it));
    }
}


template<class Vector>
void Settings::getVector(const char *name, Vector &vec) const
{
    std::string data = get<std::string>(name);
    std::vector<std::string> items, result;
    boost::trim_if(data, boost::is_any_of(";"));
    boost::split(result, data, boost::is_any_of(";"), boost::token_compress_on);
    for(std::vector<std::string>::iterator it = result.begin(), end=result.end(); it!=end; ++it)
    {
        vec.push_back(it->c_str());
    }
}


template<class T>
std::vector<T> Settings::getVector(const char *name) const
{
    std::vector<T> vec;
    getVector<T>(name, vec);
    return vec;
}



}



