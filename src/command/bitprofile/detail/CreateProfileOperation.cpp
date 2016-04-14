#include "CreateProfileOperation.hpp"


namespace Xeth{


CreateProfileOperation::CreateProfileOperation
(
    const BitProfile::Registrar &registrar,
    const QString &name,
    const QString &account,
    const QString &password,
    DataBase &database,
    Synchronizer &synchronizer,
    Notifier &notifier
) :
    _registrar(registrar),
    _name(name),
    _account(account),
    _password(password),
    _database(database),
    _synchronizer(synchronizer),
    _notifier(notifier)
{}


void CreateProfileOperation::operator()()
{
    try
    {

        EthereumKeyStore & keys = _database.getEthereumKeys();
        std::string payer = _account.toStdString();
        std::string password = _password.toStdString();
        
        if(keys.find(payer)==keys.end())
        {
            //trying to redeem key
            StealthSpendKeyRedeemer redeemer(_database);
            if(redeemer.redeem(payer, password))
            {
                _synchronizer.watchAddress(payer);
            }
        }
        else
        {
            StealthPaymentStore &payments = _database.getStealthPayments();
            if(!payments.get(payer).empty())
            {
                _synchronizer.watchAddress(payer);
            }
        }

        BitProfile::ProfileAdministrator profile = BitProfile::ProfileAdministrator::CreateProfile(_registrar, _name.toStdString(), payer, password);
        if(profile.isNull())
        {
            emitError("failed to create account ");
        }
        else
        {
            if(!_database.getBitProfiles().insert(BitProfile::ProfileDescriptor(profile)))
            {
                emitError("failed to save account ");
            }
        }
    }
    catch(const std::exception &e)
    {
        emitError(e.what());
    }
    catch(...)
    {
        emitError("create profile operation failed");
    }
}


void CreateProfileOperation::emitError(const char *msg)
{
    QString error = msg;
    error += _name;
    _notifier.emitError("bitprofile", error);
}


}
