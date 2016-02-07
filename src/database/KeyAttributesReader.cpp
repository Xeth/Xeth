#include "KeyAttributesReader.hpp"


namespace Xeth{namespace detail{

KeyAttributesReader<StealthKeyStore>::KeyAttributesReader(const std::string &path)
{
    JsonReader reader;
    if(!reader.read(path.c_str(), _json))
    {
        throw std::runtime_error("invalid json");
    }
}


KeyAttributesReader<StealthKeyStore>::KeyAttributesReader(const std::string &, const Json::Value &value):
    _json(value)
{}


std::string KeyAttributesReader<StealthKeyStore>::getAddress() const
{
    return _json["address"].asString();
}


time_t KeyAttributesReader<StealthKeyStore>::getCreationTime() const
{
    return _json["time"].asUInt();
}


KeyAttributesReader<EthereumKeyStore>::KeyAttributesReader(const std::string &path) :
    _path(path)
{}


KeyAttributesReader<EthereumKeyStore>::KeyAttributesReader(const std::string &path, const Json::Value &) :
    _path(path)
{}


std::string KeyAttributesReader<EthereumKeyStore>::getAddress() const
{
    boost::regex regex("UTC\\-\\-.+\\-\\-([0-9a-fA-F]+)$");
    boost::smatch match;

    if (boost::regex_search(_path, match, regex))
    {
        return std::string(match[1]);
    }

    return "";
}


time_t KeyAttributesReader<EthereumKeyStore>::getCreationTime() const
{
    boost::regex regex("UTC\\-\\-(.+)\\-\\-[0-9a-fA-F]+$");
    boost::smatch match;

    if (boost::regex_search(_path, match, regex))
    {
        std::string str(match[1]);
        static boost::posix_time::ptime epoch(boost::gregorian::date(1970, 1, 1));
        boost::posix_time::time_input_facet *tif = new boost::posix_time::time_input_facet;
        tif->set_iso_extended_format();
        std::istringstream is(str);
        is.imbue(std::locale(std::locale::classic(), tif));
        boost::posix_time::ptime t;
        is >> t;
        return (t - epoch).total_seconds();
    }
    else
    {
        return 0;
    }
}

}}
