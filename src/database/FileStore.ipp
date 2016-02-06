namespace Xeth{


template<class Value, class Serializer>
FileStore<Value, Serializer>::FileStore(const std::string &path, const std::string &ext) : 
    _path(path),
    _ext(ext)
{}


template<class Value, class Serializer>
bool FileStore<Value, Serializer>::importFile(const char *filename) 
{
    Reader reader;
    try
    {
        boost::filesystem::path source = boost::filesystem::absolute(filename); 
        boost::filesystem::path destination = boost::filesystem::absolute(_path);
        destination /= source.filename();

        Value content = reader(source); //make sure content is valid
        return write(destination.string(), content);
    }
    catch(...)
    {}
    return false;
}

template<class Value, class Serializer>
bool FileStore<Value, Serializer>::write(const std::string &path, const Value &val)
{
    std::ofstream file(path.c_str(), std::ofstream::trunc);
    file<<_serializer.serialize(val);
    file.close();
    return !file.bad();
}

template<class Value, class Serializer>
std::string FileStore<Value, Serializer>::makePath(const char *id) const
{
    std::string name = _path;
    name += boost::filesystem::path::preferred_separator;
    name += id;
    name += ".";
    name += _ext;
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
    std::string path = makePath(id);
    Iterator it=begin(), e=end();
    for(; it!=e; ++it)
    {
        if(it.path().string() == path)
        {
            break;
        }
    }
    return it;
}


template<class Value, class Serializer>
typename FileStore<Value, Serializer>::Iterator FileStore<Value, Serializer>::begin() const
{
    return Iterator(_path, _ext);
}


template<class Value, class Serializer>
typename FileStore<Value, Serializer>::Iterator FileStore<Value, Serializer>::end() const
{
    return Iterator();
}


template<class Value, class Serializer>
const std::string & FileStore<Value, Serializer>::getPath() const
{
    return _path;
}


}
