#pragma once 

#include <string>
#include <fstream>
#include <boost/filesystem.hpp>

#include "FileIterator.hpp"
#include "FileReader.hpp"


namespace Xeth{


template<class Value, class Serializer>
class FileStore
{
    public:
        typedef FileIterator<Value, FileReader<Value, Serializer> > Iterator;

    public:

        FileStore(const std::string &path, const std::string &ext);

        bool replace(const char *id, const Value &);
        bool insert(const char *id, const Value &);
        bool remove(const char *);

        Iterator find(const char *) const;
        Iterator begin() const;
        Iterator end() const;

    private:
        bool write(const std::string &, const Value &);
        std::string makePath(const char *id) const;

    private:
        std::string _path;
        std::string _ext;
        Serializer _serializer;
};



}

#include "FileStore.ipp"
