#include "ReadImageCommand.hpp"


namespace Xeth{


QVariant ReadImageCommand::operator()(const QString &path)
{
    QImage image(path);
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    image.save(&buffer, "PNG");
    QString base64 = QString::fromLatin1(byteArray.toBase64().data());
    base64.prepend("data:image/png;base64,");
    return base64;
}


}
