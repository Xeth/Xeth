namespace Xeth{


template<class Value, class Serializer>
ObjectReader<Value, Serializer>::ObjectReader(const Serializer &serializer) : 
    _serializer(serializer)
{}


template<class Value, class Serializer>
ObjectReader<Value, Serializer>::ObjectReader()
{}


template<class Value, class Serializer>
Value ObjectReader<Value, Serializer>::operator()(const boost::filesystem::path &path) const
{
    JsonReader reader;
    return _serializer.unserialize(reader.read(path.string().c_str()));
}


}
