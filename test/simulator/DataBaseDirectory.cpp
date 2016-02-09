#include "DataBaseDirectory.hpp"

DataBaseDirectory::DataBaseDirectory(bool create) :
    Xeth::DataBaseDirectory(GenerateRandomPath().c_str(), create)
{}


std::string DataBaseDirectory::GenerateRandomPath()
{
    std::string path = boost::lexical_cast<std::string>(time(NULL));
    path += '.';

    boost::random::mt19937 rng;
    boost::random::uniform_int_distribution<> generator;

    path += boost::lexical_cast<std::string>(generator(rng));

    return path;
}


bool DataBaseDirectory::remove()
{
    const std::string & path = getPath();
    if(path.size())
    {
        return boost::filesystem::remove_all(path);
    }

    return true;
}
