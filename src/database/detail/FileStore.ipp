namespace Xeth{


template<class Value, class Serializer>
FileStore<Value, Serializer>::FileStore(const std::string &path, const std::string &ext) : 
    _directory(path.c_str(), false),
    _ext("."+ext)
{
    _directory.createIfNotExists();
}



template<class Value, class Serializer>
bool FileStore<Value, Serializer>::write(const std::string &path, const Value &val)
{
    Writer writer(path.c_str(), true);
    return writer.write(val);
}

template<class Value, class Serializer>
std::string FileStore<Value, Serializer>::makePath(const char *id) const
{
    std::string name = _directory.getPath();
    name += boost::filesystem::path::preferred_separator;
    name += id;
    if(_ext.size())
    {
        name += _ext;
    }
    return name;
}

template<class Value, class Serializer>
bool FileStore<Value, Serializer>::replace(const char *id, const Value &val)
{
    return write(makePath(id), val);
}


template<class Value, class Serializer>
bool FileStore<Value, Serializer>::insert(const char *id, const Value &val)
{
    std::string path = makePath(id);
    if(boost::filesystem::exists(path))
    {
        return false;
    }
    return write(path, val);
}


template<class Value, class Serializer>
bool FileStore<Value, Serializer>::remove(const char *id)
{
    return boost::filesystem::remove(makePath(id));
}


template<class Value, class Serializer>
typename FileStore<Value, Serializer>::Iterator FileStore<Value, Serializer>::find(const char *id) const
{
    Iterator it=begin(), e=end();
    for(; it!=e; ++it)
    {
        if(it.path().stem().string() == id)
        {
            break;
        }
    }
    return it;
}


template<class Value, class Serializer>
Value FileStore<Value, Serializer>::get(const char *id) const
{
    Iterator it = find(id);
    if(it==end())
    {
        throw std::runtime_error("key not found");
    }
    return *it;
}


template<class Value, class Serializer>
typename FileStore<Value, Serializer>::Iterator FileStore<Value, Serializer>::begin() const
{
    return Iterator(_directory.getPath(), _ext);
}


template<class Value, class Serializer>
typename FileStore<Value, Serializer>::Iterator FileStore<Value, Serializer>::end() const
{
    return Iterator();
}


template<class Value, class Serializer>
const std::string & FileStore<Value, Serializer>::getPath() const
{
    return _directory.getPath();
}


}
