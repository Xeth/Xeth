#include "GetSyncProgressCommand.hpp"


namespace Xeth{


GetSyncProgressCommand::GetSyncProgressCommand(Synchronizer &synchronizer) : 
    _synchronizer(synchronizer)
{}


QVariant GetSyncProgressCommand::operator()()
{
    return QVariant::fromValue(_synchronizer.getSyncProgressFetcher().getValue());
}


}
