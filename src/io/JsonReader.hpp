#pragma once 

#include <json/value.h>
#include <json/reader.h>

#include <string>
#include <fstream>

#include <boost/filesystem.hpp>

namespace Xeth{


class JsonReader
{

    public:

        Json::Value read(const char *filename) const;
        bool read(const char *filename, Json::Value &result) const;
};


}
