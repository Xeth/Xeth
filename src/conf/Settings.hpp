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
#include <QMap>

#include "SettingSource.hpp"


namespace Xeth{


class Settings
{
    public:
        typedef boost::program_options::basic_option<char> option;
        typedef boost::shared_ptr<SettingSource> SourcePtr;
        typedef std::vector<SourcePtr> SourceMap;
        typedef QMap<QString, QString> DataMap;

    public:


        void addSource(const boost::shared_ptr<SettingSource> &);


        bool has(const char *) const;

        template<class T>
        T get(const char *) const;

        template<class T>
        T get(const char *, const T &) const throw();

        QString get(const char *)  const;
        QString get(const char *, const char *) const;

        template<class T, class Vector>
        void getVector(const char *, Vector &) const;

        template<class T>
        std::vector<T> getVector(const char *) const;

        template<class Vector>
        void getVector(const char *, Vector &) const;

        QStringList getVector(const char *) const;

        void set(const char *, const char *);

        void readConfigFile();
        void readFile(const char *);
        void readCommandLineArgs(int, char **);

        void set(const boost::program_options::parsed_options &);

    private:
        SourceMap _sources;
        DataMap _data;
};


}


#include "Settings.ipp"
