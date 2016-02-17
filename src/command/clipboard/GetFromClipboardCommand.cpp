#include "GetFromClipboardCommand.hpp"


namespace Xeth{


QVariant GetFromClipboardCommand::operator()()
{
    return QVariant::fromValue(QApplication::clipboard()->text());
}


}
