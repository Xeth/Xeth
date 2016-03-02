#include "HtmlExtractor.hpp"


HtmlExtractor::HtmlExtractor(const QString &path) :
    _path(MakePath(path))
{
    disableJavaScript();
    open(QUrl::fromLocalFile(MakePath(path)));
}


QWebElement HtmlExtractor::getDocument()
{
    return  getHandle().page()->mainFrame()->documentElement();
}


QWebElement HtmlExtractor::find(const QString &selector)
{
    QWebElement document = getDocument();
    return document.findFirst(selector);
}


void HtmlExtractor::move(QWebElement &element, const QString &file, bool outer)
{
    if(!element.isNull())
    {
        WriteFile(file, outer?element.toOuterXml():element.toInnerXml());
        element.removeFromDocument();
    }
}


void HtmlExtractor::move(const QString &selector, const QString &file, bool outer)
{
    QWebElement element = find(selector);
    move(element, file, outer);
}


void HtmlExtractor::moveTemplates(const QString &path)
{
    MakeDirectory(path);
    QDir dir(path);
    QWebElementCollection elements = getDocument().findAll("[type=\"text/template\"]");
    if(elements.count())
    {
        for(QWebElementCollection::iterator it = elements.begin(), end=elements.end(); it!=end; ++it)
        {
            QWebElement element = *it;
            QString filename = element.attribute("id").replace("_tpl",".tpl");
            qDebug()<<"moving element : "<<filename;
            move(element, dir.filePath(filename), false);
        }
    }
    else
    {
        qDebug()<<"no element found";
    }
}



void HtmlExtractor::saveTo(const QString &path)
{
    WriteFile(path, getContent());
}


void HtmlExtractor::save()
{
    saveTo(_path);
}


QString HtmlExtractor::getContent()
{
    return getDocument().toOuterXml().replace(QRegularExpression("(\\r\\n)+"),"\\r\\n").replace(QRegularExpression("(\\n)+"),"\n").replace(QRegularExpression("(\\r)+"),"\r");
}

