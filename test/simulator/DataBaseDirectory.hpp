#pragma once


#include <boost/random.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>

#include "database/detail/DataBaseDirectory.hpp"



class DataBaseDirectory : public Xeth::DataBaseDirectory
{
    public:
        DataBaseDirectory(bool create=false);

        bool remove();


    public:
        static std::string GenerateRandomPath();

};
