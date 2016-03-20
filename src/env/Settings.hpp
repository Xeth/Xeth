#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <boost/unordered_map.hpp>
#include <boost/program_options.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>

#include <QStringList>


namespace Xeth{


class Settings
{
    public:
        typedef boost::program_options::basic_option<char> option;

    public:

        bool has(const char *) const;

        template<class T>
        T get(const char *) const;

        template<class T>
        T get(const char *, const T &) const throw();

        const char * get(const char *)  const;
        const char * get(const char *, const char *) const;

        template<class T, class Vector>
        void getVector(const char *, Vector &) const;

        template<class T>
        std::vector<T> getVector(const char *) const;

        template<class Vector>
        void getVector(const char *, Vector &) const;

        QStringList getVector(const char *) const;

        void set(const char *, const char *);

        void readFile(const char *);
        void readCommandLineArgs(int, char **);

        void set(const boost::program_options::parsed_options &);

    private:
        boost::unordered_map<std::string, std::string> _data;
};


}


#include "Settings.ipp"
