#pragma once

#include "Settings.hpp"
#include "EthProcess.hpp"

#include <QVariant>
#include <QVariantMap>


namespace Xeth{



class ImportKeyCommand
{
    public:
        ImportKeyCommand(const Settings &);

        QVariant operator()(const QVariantMap &);

    private:
        EthProcess _process;
};



}
