#include "Store.hpp"


namespace Xeth {


class ConfigStoreDataEncoder
{
    public:
        std::string operator()(const char *, const char *);
        bool operator()(const char *, const char *, std::string &);

        std::string operator()(const std::string &);
};



typedef Store<ConfigStoreDataEncoder, std::string> ConfigStore;


}
