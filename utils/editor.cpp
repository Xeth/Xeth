#include <QApplication>
#include <QDebug>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QTextStream>


#include <iostream>

#include "lib/HtmlEditor.hpp"
#include "lib/XmlReader.hpp"

void printHelp();

void extractTemplates(const QStringList &);

void mergeTemplates(const QStringList &);
void appendJSIncludes(HtmlEditor &, const QString &, const XmlReader &, const QString &, bool);
void appendCSSIncludes(HtmlEditor &, const QString &, const XmlReader &, const QString &, bool);

void executeCommand(void (*command)(const QStringList &), const QStringList &args, int requiredArgs);
void executeIncludeCommand(void (*command)(HtmlEditor &, const QString &, const XmlReader &, const QString &, bool), const QStringList &args, const QString &depsPath, const QString &prefix, bool appendToBody);

int main(int argc, char **argv)
{

    QApplication app(argc, argv);
    QCommandLineParser parser;

    QCommandLineOption extractTemplatesOpt("extract-templates", QCoreApplication::translate("main", "extract templates"));
    QCommandLineOption mergeTemplatesOpt("merge-templates", QCoreApplication::translate("main", "merge templates"));
    QCommandLineOption helpOpt("h", QCoreApplication::translate("main", "help"));
    QCommandLineOption appendJSIncludesOpt("include-js", QCoreApplication::translate("main", "append script includes"));
    QCommandLineOption appendCssIncludesOpt("include-css", QCoreApplication::translate("main", "append css includes"));
    QCommandLineOption appendIncludePrefixOpt("prefix", QCoreApplication::translate("main", "append include path prefix"), QCoreApplication::translate("main", "prefix"), "");
    QCommandLineOption dependsPathOpt("dependencies", QCoreApplication::translate("main", "defines dependencies"), QCoreApplication::translate("main", "dependencies"), "");
    QCommandLineOption bodyOpt("body", QCoreApplication::translate("main", "append to body instead of header"), QCoreApplication::translate("main", "body"), "0");

    parser.addOption(extractTemplatesOpt);
    parser.addOption(mergeTemplatesOpt);
    parser.addOption(helpOpt);
    parser.addOption(appendJSIncludesOpt);
    parser.addOption(appendCssIncludesOpt);
    parser.addOption(appendIncludePrefixOpt);
    parser.addOption(dependsPathOpt);
    parser.addOption(bodyOpt);

    parser.process(app);

    QStringList args = parser.positionalArguments();

    if(parser.isSet(helpOpt))
    {
        printHelp();
        return 0;
    }


    if(parser.isSet(helpOpt))
    {
        printHelp();
        return 1;
    }

    if(parser.isSet(extractTemplatesOpt))
    {
        executeCommand(extractTemplates, args, 2);
    }
    else
    if(parser.isSet(mergeTemplatesOpt))
    {
        executeCommand(mergeTemplates, args, 2);
    }
    else
    {
        QString prefix = parser.value(appendIncludePrefixOpt);
        QString depsPath = parser.value(dependsPathOpt);
        qDebug()<<"body value = "<<parser.value(bodyOpt);
        bool appendToBody = parser.value(bodyOpt).toInt();
        qDebug()<<"append to body : "<<appendToBody;

        if(parser.isSet(appendJSIncludesOpt))
        {
            executeIncludeCommand(appendJSIncludes, args, depsPath, prefix, appendToBody);
        }
        else
        if(parser.isSet(appendCssIncludesOpt))
        {
            executeIncludeCommand(appendCSSIncludes, args, depsPath, prefix, appendToBody);
        }
    }
    return 0;
}


void checkArgs(const QStringList &args, int requiredArgs)
{
    if(args.count() < requiredArgs)
    {
        printHelp();
        exit(1);
    }
}

void saveHtml(HtmlEditor &editor, const QStringList &args, int index = 2)
{
    if(args.size() > index)
    {
        editor.saveTo(args[index]);
    }
    else
    {
       editor.save();
    }
}

void executeCommand(void (*command)(const QStringList &), const QStringList &args, int requiredArgs)
{
    checkArgs(args, requiredArgs);
    command(args);
}

void executeIncludeCommand(void (*command)(HtmlEditor &, const QString &, const XmlReader &, const QString &, bool), const QStringList &args, const QString &depsPath, const QString &prefix, bool toBody)
{
    checkArgs(args, 2);
    HtmlEditor editor(args[0]);
    XmlReader depsReader;
    if(depsPath.length())
    {
        depsReader.open(depsPath);
    }

    command(editor, args[1], depsReader, prefix, toBody);
    saveHtml(editor, args, 2);
}

void printHelp()
{
    std::cerr<<"invalid arguments, usage: "<<std::endl;
    std::cerr<<"--merge-templates htmlfile templatesdir [outfile] :";
    std::cerr<<std::endl;
    std::cerr<<"       merges templates from (templatesdir) with (htmlfile) and saves result in (outfile), if no (outfile) is specified saves in original htmlfile";
    std::cerr<<std::endl<<std::endl;
    std::cerr<<"--extract-templates htmlfile templatesdest [outfile]: ";
    std::cerr<<std::endl;
    std::cerr<<"       extracts templates from (htmlfile) and saves them in (templatesdest) directory, stripped html is saved in (outfile) or in original htmlfile";
    std::cerr<<std::endl;
    std::cerr<<std::endl;
    std::cerr<<"--include-js htmlfile scriptdir [outfile]: ";
    std::cerr<<std::endl;
    std::cerr<<"       appends <script> includes";
    std::cerr<<std::endl<<std::endl;
    std::cerr<<"--include-css htmlfile cssdir [outfile]: ";
    std::cerr<<std::endl;
    std::cerr<<"       appends <link rel=\"stylesheet\"> includes";
    std::cerr<<"--prefix=prefix";
    std::cerr<<std::endl;
    std::cerr<<"       append includes path prefix";
    std::cerr<<std::endl<<std::endl;
    std::cerr<<"--dependencies=file: ";
    std::cerr<<std::endl;
    std::cerr<<"       use dependencies file";
    std::cerr<<"--body=0|1";
    std::cerr<<std::endl;
    std::cerr<<"       append to body instead of header, default=0";
    std::cerr<<std::endl<<std::flush;
}



void extractTemplates(const QStringList &args)
{
    HtmlEditor editor(args[0]);
    QWebElementCollection items = editor.removeAll("[type=\"text/template\"]");
    if(items.count())
    {
        QDir dir(args[1]);
        for(QWebElementCollection::iterator it = items.begin(), end=items.end(); it!=end; ++it)
        {
            QWebElement element = *it;
            QString filename = element.attribute("id").replace("_tpl",".tpl");
            qDebug()<<"moving element : "<<filename;
            WriteFile(dir.filePath(filename), element.toInnerXml());
        }
        saveHtml(editor, args);
    }
}

void mergeTemplates(const QStringList &args)
{
    HtmlEditor editor(args[0]);

    QDirIterator it(args[1], QDir::Files);
    while(it.hasNext())
    {
        QString path = it.next();
        QFileInfo info(path);
        QString id = info.baseName();
        id+="_tpl";

        QString content = "<script type=\"text/template\" id=\"";
        content += id;
        content += "\">\r\n";
        content += GetFileContent(path);
        content += "\r\n</script>";
        editor.appendToBody(content);
    }

    saveHtml(editor, args);
}

void appendInclude(HtmlEditor &editor, QMap<QString, QString> &map, const QString &key, const XmlReader &depsReader, bool toBody)
{
    qDebug()<<"including "<<key;
    QDomElement deps = depsReader.findByAttribute("file", key);
    if(!deps.isNull())
    {
        QDomElement dependency = deps.firstChildElement();
        while(!dependency.isNull())
        {
            QString depKey = dependency.text();
            qDebug()<<"dependency found : "<<depKey;
            if(map.contains(depKey))
            {
                appendInclude(editor, map, depKey, depsReader, toBody);
            }
            dependency = dependency.nextSiblingElement();
        }
    }
    if(toBody)
    {
        editor.appendToBody(map[key], true);
    }
    else
    {
        editor.appendToHeader(map[key]);
    }
    map.remove(key);
}


void appendIncludes(HtmlEditor &editor, const QString &dir, const QString &ext, QString (*parser)(const QString &), const XmlReader &deps, const QString &prefix, bool toBody)
{

    QMap<QString, QString> includesMap;

    QDirIterator it(dir, QStringList() << (QString("*.")+ext), QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        it.next();
        QFileInfo info = it.fileInfo();
        QString path = prefix;
        path += info.filePath();
        includesMap[info.fileName()] = parser(path);
    }

    while(!includesMap.empty())
    {
        appendInclude(editor, includesMap, includesMap.firstKey(), deps, toBody);
    }
}






QString jsIncludeParser(const QString &path)
{
    QString tag = "\r\n<script type='text/javascript' src='";
    tag += path;
    tag += "'></script>";
    return tag;
}

void appendJSIncludes(HtmlEditor &editor, const QString &dir, const XmlReader &depsReader, const QString &prefix, bool toBody)
{
    appendIncludes(editor, dir, "js", jsIncludeParser, depsReader, prefix, toBody);

}

QString cssIncludeParser(const QString &path)
{
    QString tag = "\r\n<link rel=\"stylesheet\" type=\"text/css\" href=\"";
    tag += path;
    tag += "\" />";
    return tag;
}


void appendCSSIncludes(HtmlEditor &editor, const QString &dir, const XmlReader &depsReader, const QString &prefix, bool toBody)
{
    appendIncludes(editor, dir, "css", cssIncludeParser, depsReader, prefix, toBody);
}


