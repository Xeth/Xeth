namespace Xeth{


template<class Value, class Serializer>
FileReader<Value, Serializer>::FileReader(const Serializer &serializer) : 
    _serializer(serializer)
{}


template<class Value, class Serializer>
FileReader<Value, Serializer>::FileReader()
{}


template<class Value, class Serializer>
Value FileReader<Value, Serializer>::operator()(const boost::filesystem::path &path) const
{
    std::ifstream stream(fs::absolute(path).string().c_str());
    std::string content(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>());
    return _serializer.unserialize(content);
}


}
