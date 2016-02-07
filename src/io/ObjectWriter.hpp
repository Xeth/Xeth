#pragma once 

#include <boost/filesystem.hpp>

#include "JsonWriter.hpp"

namespace Xeth{


template<class Value, class Serializer>
class ObjectWriter
{
    public:
        ObjectWriter(const char *path, bool truncate);
        ObjectWriter(const char *path, const Serializer &, bool truncate);

        bool write(const Value &);


    private:
        Serializer _serializer;
        JsonWriter _writer;
};


}

#include "ObjectWriter.ipp"
