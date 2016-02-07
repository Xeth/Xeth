namespace Xeth{


template<class Value, class Serializer>
ObjectReader<Value, Serializer>::ObjectReader(const Serializer &serializer) : 
    _serializer(serializer)
{}


template<class Value, class Serializer>
ObjectReader<Value, Serializer>::ObjectReader()
{}


template<class Value, class Serializer>
Value ObjectReader<Value, Serializer>::read(const char *path) const
{
    JsonReader reader;
    return _serializer.unserialize(reader.read(path));
}

template<class Value, class Serializer>
Value ObjectReader<Value, Serializer>::read(const boost::filesystem::path &path) const
{
    return read(path.string().c_str());
}

template<class Value, class Serializer>
Value ObjectReader<Value, Serializer>::operator()(const boost::filesystem::path &path) const
{
    return read(path);
}


}
