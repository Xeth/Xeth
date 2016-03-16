#include "FileMinifier.hpp"


QString WhitespaceRemover::operator()(const QString &content)
{
    return content.simplified();
}
