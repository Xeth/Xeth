namespace Xeth{


template<class Store>
KeyAttributesReader<Store>::KeyAttributesReader(const std::string &path) : 
    Base(path)
{}


template<class Store>
KeyAttributesReader<Store>::KeyAttributesReader(const std::string &path, const Json::Value &json) :
    Base(path, json)
{}



}
