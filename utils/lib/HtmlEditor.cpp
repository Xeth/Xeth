#include "HtmlEditor.hpp"
#include <QDebug>


HtmlEditor::HtmlEditor(const QString &path) :
    _path(MakePath(path))
{
    disableJavaScript();
    open(QUrl::fromLocalFile(MakePath(path)));
}


QWebElement HtmlEditor::getDocument()
{
    return  getHandle().page()->mainFrame()->documentElement();
}


QWebElement HtmlEditor::find(const QString &selector)
{
    QWebElement document = getDocument();
    return document.findFirst(selector);
}


QWebElement HtmlEditor::remove(const QString &selector)
{
    QWebElement element = find(selector);
    if(!element.isNull())
    {
        element.removeFromDocument();
    }
    return element;
}


QWebElementCollection HtmlEditor::removeAll(const QString &selector)
{
    QWebElementCollection elements = getDocument().findAll(selector);
    for(QWebElementCollection::iterator it = elements.begin(), end=elements.end(); it!=end; ++it)
    {
        QWebElement element = *it;
        element.removeFromDocument();
    }
    return elements;
}

void HtmlEditor::saveTo(const QString &path)
{
    WriteFile(path, getContent());
}


void HtmlEditor::save()
{
    saveTo(_path);
}


QString HtmlEditor::getContent()
{
    return getDocument().toOuterXml().replace(QRegularExpression("(\\r\\n)+"),"\\r\\n").replace(QRegularExpression("(\\n)+"),"\n").replace(QRegularExpression("(\\r)+"),"\r");
}



void HtmlEditor::appendTo(const QString &selector, const QString &content, bool outer)
{
    QWebElement element = find(selector);
    if(!element.isNull())
    {
        if(outer)
        {
            element.appendOutside(content);
        }
        else
        {
            element.appendInside(content);
        }
    }
}

void HtmlEditor::prependTo(const QString &selector, const QString &content, bool outer)
{
    QWebElement element = find(selector);
    if(!element.isNull())
    {
        if(outer)
        {
            element.prependOutside(content);
        }
        else
        {
            element.prependInside(content);
        }
    }
}


void HtmlEditor::appendToHeader(const QString &text)
{
    forceInsert("</\\s*head\\s*>", text, true);
}


void HtmlEditor::appendToBody(const QString &text, bool outer)
{
    appendTo("body", text, outer);
}

void HtmlEditor::prependToHeader(const QString &text)
{
    forceInsert("<\\s*head\\s*>", text, false);
}


void HtmlEditor::prependToBody(const QString &text, bool outer)
{
    prependTo("body", text, outer);
}


void HtmlEditor::forceInsert(const QString &pattern, const QString &text, bool insertBefore)
{
    QWebElement document = getDocument();
    QString content = document.toOuterXml();
    QRegExp regex(pattern);
    int pos = regex.indexIn(content);
    if(pos != -1 )
    {
        if(insertBefore)
        {
            content.insert(pos, text);
        }
        else
        {
            QString cap = regex.cap(0);
            content.insert(pos + cap.length(), text);
        }
    }
    getHandle().page()->mainFrame()->setHtml(content);
}



