#pragma once

#include "Settings.hpp"
#include "process/EthProcess.hpp"
#include "synchronizer/Synchronizer.hpp"
#include "io/JsonReader.hpp"

#include <QVariant>
#include <QVariantMap>


namespace Xeth{



class ImportPresaleKeyCommand
{
    public:
        ImportPresaleKeyCommand(const Settings &, Synchronizer &);

        QVariant operator()(const QVariantMap &);

    private:
        EthProcess _process;
        Synchronizer &_synchronizer;
};



}
