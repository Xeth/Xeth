
#include <QDebug>


inline bool NullFileFilter::operator()(const QFileInfo &) const
{
    return true;
}


inline FileExtensionFilter::FileExtensionFilter(const QString &extension) :
    _extension(extension)
{}


inline bool FileExtensionFilter::operator()(const QFileInfo &info) const
{
    return info.completeSuffix() == _extension;
}



template<class Parser, class FileFilter>
FileParser<Parser, FileFilter>::FileParser()
{}


template<class Parser, class FileFilter>
FileParser<Parser, FileFilter>::FileParser(const Parser &parser) : 
    _parser(parser)
{}

template<class Parser, class FileFilter>
FileParser<Parser, FileFilter>::FileParser(const FileFilter &filter) : 
    _filter(filter)
{}


template<class Parser, class FileFilter>
FileParser<Parser, FileFilter>::FileParser(const Parser &parser, const FileFilter &filter) : 
    _parser(parser),
    _filter(filter)
{}


template<class Parser, class FileFilter>
bool FileParser<Parser, FileFilter>::parseDirectory(const QString &src, const QString &dest)
{
    QDirIterator it(src, QDir::Files, QDirIterator::Subdirectories);
    while(it.hasNext())
    {
        QFileInfo info(it.next());
        QString srcFile = info.filePath();
        if(srcFile.contains("vendor") || !_filter(info))
        {
            continue;
        }
        QString destFile = srcFile;
        destFile.replace(0, src.length(), dest);

        if(!parse(srcFile, destFile))
        {
            return false;
        }
    }
    return true;
}


template<class Parser, class FileFilter>
bool FileParser<Parser, FileFilter>::parse(const QString &src, const QString &dest)
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


