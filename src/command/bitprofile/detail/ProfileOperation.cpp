#include "ProfileOperation.hpp"


namespace Xeth{


ProfileOperation::ProfileOperation
(
    const BitProfile::ProfileAdministrator &admin,
    const QString &password,
    Notifier &notifier
) : 
    _admin(admin),
    _password(password),
    _notifier(notifier)
{}


void ProfileOperation::operator()()
{
    try
    {
        execute();
    }
    catch(const std::exception &e)
    {
        emitError(e.what());
    }
    catch(...)
    {
        emitError("failed to link stealth address");
    }
}

void ProfileOperation::emitData(const QString &key, const QVariant &value)
{
    _notifier.emitData("bitprofile", getProfileUri(), "payments", value);
}

void ProfileOperation::emitError(const char *error)
{
    _notifier.emitObjectError("bitprofile", getProfileUri(), error);
}


QString ProfileOperation::getProfileUri()
{
    return _admin.getProfile().getURI().toString().c_str();
}

}
