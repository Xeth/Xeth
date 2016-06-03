#include "ListRegistrarsCommand.hpp"

namespace Xeth{


ListRegistrarsCommand::ListRegistrarsCommand(Ethereum::Connector::Provider &provider, const Settings &settings) :
    _provider(provider),
    _settings(settings)
{}


QVariant ListRegistrarsCommand::operator()(const QVariantMap &request)
{
    BitProfile::MasterRegistrar master(_provider, GetBitprofileNetwork(_settings));
    BitProfile::MasterRegistrar::URIList uris = master.getURIList();
    
    return makeList(request.contains("offset")?uris.at(request["offset"].toInt()): uris.begin(), uris.end(), request.contains("limit")?request["limit"].toInt():100);

}


template<class Iterator>
QVariant ListRegistrarsCommand::makeList(Iterator begin, Iterator end, size_t limit)
{
    QStringList result;
    for(size_t i=0; begin!=end && i<limit; ++i, ++begin)
    {
        result.append(begin->toString().c_str());
    }

    return result;
}


}
