#include "ResolvePaymentAddressCommand.hpp"


namespace Xeth{


ResolvePaymentAddressCommand::ResolvePaymentAddressCommand(Ethereum::Connector::Provider &provider, const Settings &settings) :
    _resolver(provider, GetBitprofileNetwork(settings))
{}


QVariant ResolvePaymentAddressCommand::operator()(const QString &uri)
{
    BitProfile::Profile profile = _resolver.lookupProfile(uri.toStdString());
    if(profile.isNull())
    {
        return QVariant::fromValue(false);
    }

    return QString(profile.getPaymentAddress().c_str());
}


}
