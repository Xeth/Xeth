#include "HtmlMerger.hpp"
#include <QDebug>

HtmlMerger::HtmlMerger(const QString &file) : 
    SyncWebView(QUrl::fromLocalFile(MakePath(file))),
    _path(MakePath(file))
{}


QString HtmlMerger::escapeText(const QString &text)
{
    QString parsed = text;
    parsed.replace("\"", "\\\"").replace("\n","\\n").replace("\r","\\r");
    return parsed;
}


void HtmlMerger::appendText(const QString &text)
{
    QString js = "document.body.innerHTML += (\"\\r\\n\"+\"";
    js += escapeText(text);
    js += "\"+\"\\r\\n\")";
    getHandle().page()->mainFrame()->evaluateJavaScript(js);
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
    QFile file(MakePath(path));
    if(!file.open(QFile::WriteOnly | QFile::Text| QFile::Truncate))
    {
        qDebug()<<"failed to open file: "<<path;
    }
    QTextStream stream(&file);
    stream<<getContent();
    file.close();
}


QString HtmlMerger::getContent()
{
    return getHandle().page()->mainFrame()->toHtml();
}
