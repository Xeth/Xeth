#pragma once

#include <string>
#include <sstream>
#include <stdexcept>

#include <boost/filesystem.hpp>

#include <QDebug>

#ifdef __WINDOWS_OS__
#include <shlobj.h>
#endif

#include "Settings.hpp"

namespace Xeth{



class DataBaseDirectory
{
    public:
        DataBaseDirectory(const Settings &, bool create=false);
        DataBaseDirectory(const char *path, bool create=false);
        DataBaseDirectory(const boost::filesystem::path &, bool create=false);
        DataBaseDirectory(bool create=false);

        const boost::filesystem::path & getPath() const;
        std::string toString() const;

        void createIfNotExists();
        bool createIfNotExistsNoThrow();

    public:
        static boost::filesystem::path GetDefaultPath();
        static boost::filesystem::path ResolvePath(const char *);

    private:
        boost::filesystem::path _path;

};


}
