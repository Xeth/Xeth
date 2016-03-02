#include "utils.hpp"

QString MakePath(const QString &path)
{
    QFileInfo info(path);
    return info.absoluteFilePath();
}
