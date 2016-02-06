#pragma once

#include "Settings.hpp"
#include "process/EthProcess.hpp"

#include <QVariant>
#include <QVariantMap>


namespace Xeth{



class ImportPresaleKeyCommand
{
    public:
        ImportPresaleKeyCommand(const Settings &);

        QVariant operator()(const QVariantMap &);

    private:
        EthProcess _process;
};



}
