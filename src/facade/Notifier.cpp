#include "Notifier.hpp"

namespace Xeth{

void Notifier::emitError(const QString &msg)
{
    emit Error(msg);
}

void Notifier::emitMessage(const QString &msg)
{
    emit Message(msg);
}

void Notifier::emitReady()
{
    emit Ready();
}


}
