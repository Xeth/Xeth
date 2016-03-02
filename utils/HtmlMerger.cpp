#include "HtmlMerger.hpp"
#include <QDebug>

HtmlMerger::HtmlMerger(const QString &file) : 
    _path(MakePath(file)),
    _content(getFileContent(_path))
{}


QString HtmlMerger::parseText(const QString &text)
{
    QString parsed = "\r\n";
    parsed += text;
    parsed += "\r\n";
    return parsed;
}


void HtmlMerger::appendText(const QString &text)
{
    int index = _content.indexOf("</body>");
    if(index >= 0)
    {
        _content.insert(index+7, parseText(text));
    }
}



void HtmlMerger::appendFile(const QString &path)
{
    appendText(getFileContent(path));
}


QString HtmlMerger::getFileContent(const QString &path)
{
    QFile file(MakePath(path));
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug()<<"failed to open file: "<<path;
    }

    QTextStream stream(&file);
    return stream.readAll();
}


void HtmlMerger::appendTemplateFile(const QString &path)
{
    QFileInfo info(path);
    QString id = info.baseName();
    id+="_tpl";

    QString content = "<script type=\"text/template\" id=\"";
    content += id;
    content += "\">\r\n";
    content += getFileContent(path);
    content += "\r\n</script>";
    appendText(content);
}


void HtmlMerger::appendTemplatesFromDir(const QString &path)
{
    QDirIterator it(path, QDir::Files);
    while(it.hasNext())
    {
        appendTemplateFile(it.next());
    }
}


void HtmlMerger::save()
{
    saveTo(_path);
}


void HtmlMerger::saveTo(const QString &path)
{
    WriteFile(path, getContent());
}


QString HtmlMerger::getContent()
{
    return _content;
}
