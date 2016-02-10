
#include "Settings.hpp"

namespace Xeth{


bool Settings::has(const char *name) const
{
    boost::unordered_map<std::string, std::string>::const_iterator it= _data.find(name);
    return it!=_data.end();
}


const char * Settings::get(const char *name) const
{
    boost::unordered_map<std::string, std::string>::const_iterator it= _data.find(name);
    if(it==_data.end())
    {
        std::stringstream err;
        err<<"settings ["<<name<<"] not found";
        throw std::runtime_error(err.str());
    }
    return it->second.c_str();
}




const char * Settings::get(const char *name, const char *defaultVal) const
{
    boost::unordered_map<std::string, std::string>::const_iterator it= _data.find(name);
    if(it==_data.end())
    {
        return defaultVal;
    }
    return it->second.c_str();
}




void Settings::set(const char *name, const char *value)
{
    _data.insert(std::make_pair(name, value));
}



void Settings::readFile(const char *path)
{
    std::ifstream file(path);
    boost::program_options::options_description desc;
    set(boost::program_options::parse_config_file(file, desc, true));
}


void Settings::set(const boost::program_options::parsed_options &parsed)
{
    BOOST_FOREACH(const option &opt, parsed.options)
    {
        _data[opt.string_key] = *opt.value.begin();
    }
}


void Settings::readCommandLineArgs(int argc, char **argv)
{
    boost::program_options::options_description desc;
    set(boost::program_options::command_line_parser(argc, argv).options(desc).allow_unregistered().run());
}

QStringList Settings::getVector(const char *name) const
{
    QStringList vector;
    getVector(name, vector);
    return vector;
}

}
