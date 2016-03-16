
#include <QDebug>
template<class Parser>
FileParser<Parser>::FileParser()
{}


template<class Parser>
FileParser<Parser>::FileParser(const Parser &parser) : 
    _parser(parser)
{}


template<class Parser>
bool FileParser<Parser>::parseDirectory(const QString &src, const QString &dest)
{
    QDirIterator it(src, QDir::Files, QDirIterator::Subdirectories);
    while(it.hasNext())
    {
        QFileInfo info(it.next());
        QString srcFile = info.filePath();
        QString destFile = srcFile;
        destFile.replace(0, src.length(), dest);

        if(!parse(srcFile, destFile))
        {
            return false;
        }
    }
    return true;
}


template<class Parser>
bool FileParser<Parser>::parse(const QString &src, const QString &dest)
{
    QFile input(src), output(dest);

    if (!input.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug()<<"failed to open "<<src;
        return false;
    }

    if(!output.open(QFile::WriteOnly|QFile::Truncate|QFile::Text))
    {
        qDebug()<<"failed to open "<<dest<<" for writting";
        return false;
    }

    QTextStream inStream(&input);
    QTextStream outStream(&output);
    outStream<<_parser(inStream.readAll());
    qDebug()<<dest<<" parsed";
    input.close();
    output.close();
    return true;
}


