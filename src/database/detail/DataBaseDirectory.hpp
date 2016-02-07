#pragma once

#include <string>
#include <sstream>
#include <stdexcept>

#include <boost/filesystem.hpp>

#include <QDebug>


namespace Xeth{



class DataBaseDirectory
{
    public:
        DataBaseDirectory(const char *path, bool create=false);
        DataBaseDirectory(bool create=false);

        const std::string & getPath() const;

        void createIfNotExists();
        bool createIfNotExistsNoThrow();

    public:
        static std::string GetDefaultPath();
        static std::string ResolvePath(const char *);

    private:
        std::string _path;

};


}
