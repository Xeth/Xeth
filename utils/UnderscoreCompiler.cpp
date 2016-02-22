#include "UnderscoreCompiler.hpp"



bool UnderscoreCompiler::compile(const QString &src, const QString &dest)
{
    QDirIterator it(src, QDir::Files);
    while(it.hasNext())
    {
        QFileInfo info(it.next());
        QString out = dest;
        out += QDir::separator();
        out += info.fileName();
        if(!compileFile(info.filePath(), out))
        {
            return false;
        }
    }
    return true;
}


bool UnderscoreCompiler::compileFile(const QString &src, const QString &dest)
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
    QString content = inStream.readAll().replace("'", "\\'").replace("\n"," ").replace("\r"," ");
    QString js = "_.template('";
    js += content;
    js += "').source;";
    QString result = _invoker.execute(js).toString();
    outStream<<result;
    qDebug()<<dest<<" compiled";
    input.close();
    output.close();
    return true;
}


