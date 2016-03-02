#include <QApplication>
#include <QDebug>
#include <QCommandLineParser>
#include <QCommandLineOption>


#include <iostream>

#include "HtmlMerger.hpp"

int main(int argc, char **argv)
{

    QApplication app(argc, argv);
    QCommandLineParser parser;

    QCommandLineOption unpackOpt("u", QCoreApplication::translate("main", "unpack templates"));
    QCommandLineOption packOpt("p", QCoreApplication::translate("main", "pack templates"));

    parser.addOption(unpackOpt);
    parser.addOption(packOpt);

    parser.process(app);

    QStringList args = parser.positionalArguments();

    if(args.size()<2||(!parser.isSet(packOpt)&&!parser.isSet(unpackOpt)))
    {
        std::cerr<<"invalid arguments, usage: [-u|-p] htmlfile templatesdir [outfile]"<<std::endl<<std::flush;
        return 1;
    }

    if(parser.isSet(packOpt))
    {
        HtmlMerger merger(args[0]);
        merger.appendTemplatesFromDir(args[1]);
        if(args.size()>2)
        {
            merger.saveTo(args[2]);
        }
        else
        {
            merger.save();
        }
    }
    else
    {
        std::cerr<<"not implemented"<<std::endl<<std::flush;
        return 2;
    }

    return 0;
}
