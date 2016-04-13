#include "ValidateIdCommand.hpp"


namespace Xeth{


ValidateIdCommand::ValidateIdCommand() :
    _pattern("[a-z0-9_]+")
{}


QVariant ValidateIdCommand::operator()(const QString &id)
{
    return QVariant::fromValue(_pattern.exactMatch(id));
}


}
