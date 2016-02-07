namespace Xeth{


template<class Data>
Data DataSerializer<Data>::operator()(const char *, const char *value) const
{
    return boost::lexical_cast<Data>(value);
}


template<class Data>
bool DataSerializer<Data>::operator()(const char *, const char *value, Data &data) const
{
    try
    {
        data = boost::lexical_cast<Data>(value);
        return true;
    }
    catch(...)
    {}
    return false;
}


template<class Data>
std::string DataSerializer<Data>::operator ()(const Data &data) const
{
    return boost::lexical_cast<std::string>(data);
}


}
