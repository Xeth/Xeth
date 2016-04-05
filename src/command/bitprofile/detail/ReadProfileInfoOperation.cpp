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
                detailsPath = namereg.resolve(detailsPath);
                if(!detailsPath.length())
                {
                    emitData(QVariantMap());
                    return;
                }
            }
            emitData(reader.readJson(detailsPath).toVariantMap());
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
