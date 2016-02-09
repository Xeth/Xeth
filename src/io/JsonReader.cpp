#include "JsonReader.hpp"

namespace Xeth{

Json::Value JsonReader::read(const char *filename) const
{
    Json::Value result;
    if(!read(filename, result))
    {
        throw std::runtime_error("invalid json");
    }
    return result;
}

bool JsonReader::read(const char *filename, Json::Value &result) const
{
    Json::Reader reader;
    std::ifstream stream(boost::filesystem::absolute(filename).string().c_str());
    if(!stream)
    {
        return false;
    }
    std::string content;
    stream.seekg(0, std::ios::end);
    content.resize(stream.tellg());
    stream.seekg(0, std::ios::beg);
    stream.read(&content[0], content.size());
    stream.close();
    return reader.parse(content, result, false);
}

}
