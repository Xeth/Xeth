#include "ReadProfileInfoOperation.hpp"


namespace Xeth{


ReadProfileInfoOperation::ReadProfileInfoOperation(const BitProfile::Profile &profile, const Settings &settings, Notifier &notifier) :
    _profile(profile),
    _settings(settings),
    _notifier(notifier)
{}


void ReadProfileInfoOperation::operator()()
{
    try
    {
        QString detailsPath = _profile.get("details").c_str();

        if(!detailsPath.length())
        {
            emitData(QVariantMap());
        }
        else
        {
            IpfsReader reader(_settings);
            if(detailsPath.contains("ipns://"))
            {
                IpfsNameRegistrar namereg(_settings);
                detailsPath = namereg.resolve(detailsPath.remove(0, 7));
                if(!detailsPath.length())
                {
                    emitData(QVariantMap());
                    return;
                }
            }
            else
            {
                detailsPath.remove(0, 7);
            }
            QVariantMap details = reader.readJson(detailsPath).toVariantMap();
            if(details.contains("avatar"))
            {
                details["avatar"] = QString(reader.readBytes(details["avatar"].toString().remove(0,7)));
            }
            emitData(details);
        }
    }
    catch(const std::exception &e)
    {
        emitError(e.what());
    }
    catch(...)
    {
        emitError("failed to read profile details");
    }
}

void ReadProfileInfoOperation::emitError(const char *error)
{
    _notifier.emitObjectError("bitprofile", getProfileUri(), error);
}


void ReadProfileInfoOperation::emitData(const QVariantMap &data)
{
    _notifier.emitData("bitprofile", getProfileUri(), "details", data);
}

QString ReadProfileInfoOperation::getProfileUri()
{
    return _profile.getURI().toString().c_str();
}

}
