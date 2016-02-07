#pragma once 

#include <json/value.h>
#include <json/writer.h>

#include <string>
#include <fstream>

#include <boost/filesystem.hpp>

namespace Xeth{


class JsonWriter
{

    public:
        JsonWriter(const char *path, bool truncate);
        bool write(const Json::Value &data);

    private:
        std::ofstream _stream;
        Json::FastWriter _parser;
};


}
