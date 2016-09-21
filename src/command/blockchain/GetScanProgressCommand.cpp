#include "GetScanProgressCommand.hpp"

namespace Xeth{


GetScanProgressCommand::GetScanProgressCommand(Synchronizer &synchronizer) : 
    _synchronizer(synchronizer)
{}


QVariant GetScanProgressCommand::operator()()
{
    return QVariant::fromValue(_synchronizer.getScanner().getProgress().getValue());
}


}
