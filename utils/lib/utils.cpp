#include "utils.hpp"

QString MakePath(const QString &path)
{
    QFileInfo info(path);
    return info.absoluteFilePath();
}

void MakeDirectory(const QString &path)
{
    QDir dir;
    if(!dir.mkpath(MakePath(path)))
    {
        qDebug()<<"failed to create directory : "<<path;
    }
}


void WriteFile(const QString &path, const QString &content)
{
    QFile file(MakePath(path));
    if(!file.open(QFile::WriteOnly | QFile::Text| QFile::Truncate))
    {
        qDebug()<<"failed to open file: "<<path;
    }
    QTextStream stream(&file);
    stream<<content;
    file.close();
}


QString GetFileContent(const QString &path)
{
    QFile file(MakePath(path));
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug()<<"failed to open file: "<<path;
    }

    QTextStream stream(&file);
    return stream.readAll();
}
