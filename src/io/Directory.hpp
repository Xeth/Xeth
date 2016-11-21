#pragma once

#include <string>
#include <sstream>
#include <stdexcept>

#include <boost/filesystem.hpp>

#include <QDebug>


#include "conf/Settings.hpp"
#include "ApplicationPath.hpp"

namespace Xeth{



class Directory
{
    public:
        typedef boost::filesystem::path Path;

    public:
        Directory(const Settings &, bool create=false);
        Directory(const char *path, bool create=false);
        Directory(const boost::filesystem::path &, bool create=false);
        Directory(bool create=false);

        const Path & getPath() const;
        std::string toString() const;

        void createIfNotExists();
        bool createIfNotExistsNoThrow();

    public:
        static boost::filesystem::path GetDefaultPath();
        static boost::filesystem::path ResolvePath(const char *);

    private:
        Path _path;

};


}
