#include <string>
#include <iostream>

#include <QApplication>
#include <QDebug>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QTextStream>

#include "ethcrypto/key/PublicKey.hpp"
#include "ethcrypto/serialization/PublicKeySerializer.hpp"
#include "ethcrypto/encoding/HexEncoder.hpp"
#include "ethstealth/Literal.hpp"

#include "detail/StealthSpendKeyRedeemer.hpp"


int main(int argc, char **argv)
{

    QApplication app(argc, argv);
    QCommandLineParser optParser;

    Xeth::Settings settings;
    settings.readCommandLineArgs(argc, argv);

    Xeth::DataBase database(settings);

    QCommandLineOption addressOpt("address", QCoreApplication::translate("main", "address"));
    QCommandLineOption stealthOpt("stealth", QCoreApplication::translate("main", "stealth"));
    QCommandLineOption ephemOpt("ephem", QCoreApplication::translate("main", "ephem"));
    QCommandLineOption passwordOpt("password", QCoreApplication::translate("main", "password"));

    optParser.addOption(addressOpt);
    optParser.addOption(ephemOpt);
    optParser.addOption(passwordOpt);

    optParser.process(app);
    QStringList args = optParser.positionalArguments();


    if(!optParser.isSet(passwordOpt)||!optParser.isSet(addressOpt)||!optParser.isSet(stealthOpt))
    {
        qDebug()<<"\n\n\n--------------------------------------------------------------------";
        qDebug()<<"usage: --stealth=stealth_address --address=payment_receiver_address --password=stealth_key_password";
        qDebug()<<"  or : --stealth=stealth_address --address=payment_receiver_address --password=stealth_key_password --ephem=ephem_pubkey_hex";
        return -1;
    }

    std::string address  = optParser.value(addressOpt).toStdString();
    std::string stealth  = optParser.value(stealthOpt).toStdString();
    std::string password = optParser.value(passwordOpt).toStdString();

    Xeth::StealthKey stealthKey = database.getStealthKeys().get(stealth.c_str());

    if(optParser.isSet(ephemOpt))
    {
        Ethereum::PublicKeySerializer serializer;
        std::string ephemStr = optParser.value(ephemOpt).toStdString();
        Ethereum::PublicKey ephem = serializer.unserialize(ephemStr.c_str(), ephemStr.size());

        Xeth::StealthResolver resolver(stealthKey);
        Ethereum::Stealth::SharedSecret secret;
        if(!resolver.uncover(Ethereum::Address(address), ephem, secret))
        {
            qDebug()<<"failed to uncover stealth payment";
            return -2;
        }

        Ethereum::Stealth::RedeemKeyFactory redeemFactory;
        Xeth::CipherFactory cipherFactory;
        
        Xeth::EthereumKey key = redeemFactory.create(stealthKey.getSpendPrivateKeys()[0].unlock(password), secret, cipherFactory.create(), password);

        if(!database.getEthereumKeys().insert(key))
        {
            qDebug()<<"failed to save created key";
            return -3;
        }

    }
    else
    {

        //check unredeemed keys
        Xeth::StealthSpendKeyRedeemer redeemer(database);
        if(!redeemer.redeem(address, password))
        {
            qDebug()<<"failed to redeem stealth key";
            return -4;
        }
    }
    qDebug()<<"stelth payment redeemed; key saved in keystore";
    return 0;
}
