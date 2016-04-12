#include "JsonWriter.hpp"


namespace Xeth{

JsonWriter::JsonWriter(const char *path, bool truncate) :
    _stream(path, truncate ? std::ofstream::trunc : std::ofstream::app)
{
    _stream.exceptions(std::ios::failbit); 
}


bool JsonWriter::write(const Json::Value &data)
{
    _stream<<_parser.write(data);
    _stream.close();
    return true;
}


}
