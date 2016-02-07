namespace Xeth{


template<class Value, class Serializer>
ObjectWriter<Value, Serializer>::ObjectWriter(const char *path, const Serializer &serializer, bool truncate) : 
    _writer(path, truncate),
    _serializer(serializer)
{}


template<class Value, class Serializer>
ObjectWriter<Value, Serializer>::ObjectWriter(const char *path, bool truncate):
    _writer(path, truncate)
{}


template<class Value, class Serializer>
bool ObjectWriter<Value, Serializer>::write(const Value &data)
{
    return _writer.write(_serializer.serializeToJson(data));
}


}
