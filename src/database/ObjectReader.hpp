#pragma once 


#include "JsonReader.hpp"


namespace Xeth{


template<class Value, class Serializer>
class ObjectReader
{
    public:
        ObjectReader();
        ObjectReader(const Serializer &);

        Value operator()(const boost::filesystem::path &) const;


    private:
        Serializer _serializer;
};


}

#include "ObjectReader.ipp"
