#pragma once 


#include <fstream>
#include <iterator>

#include <boost/filesystem.hpp>


namespace Xeth{


template<class Value, class Serializer>
class FileReader
{
    public:
        FileReader();
        FileReader(const Serializer &);

        Value operator()(const boost::filesystem::path &) const;


    private:
        Serializer _serializer;
};


}

#include "FileReader.ipp"
