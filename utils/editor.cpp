#include <QApplication>
#include <QDebug>
#include <QCommandLineParser>
#include <QCommandLineOption>


#include <iostream>

#include "lib/HtmlMerger.hpp"
#include "lib/HtmlExtractor.hpp"

void printHelp()
{
    std::cerr<<"invalid arguments, usage: "<<std::endl;
    std::cerr<<"-m htmlfile templatesdir [outfile] :";
    std::cerr<<std::endl;
    std::cerr<<"       merges templates from (templatesdir) with (htmlfile) and saves result in (outfile), if no (outfile) is specified saves in original htmlfile";
    std::cerr<<std::endl<<std::endl;
    std::cerr<<"-e htmlfile templatesdest [outfile]: ";
    std::cerr<<std::endl;
    std::cerr<<"       extracts templates from (htmlfile) and saves them in (templatesdest) directory, stripped html is saved in (outfile) or in original htmlfile";
    std::cerr<<std::endl<<std::flush;
}

int main(int argc, char **argv)
{

    QApplication app(argc, argv);
    QCommandLineParser parser;

    QCommandLineOption unpackOpt("e", QCoreApplication::translate("main", "extract templates"));
    QCommandLineOption packOpt("m", QCoreApplication::translate("main", "merge templates"));
    QCommandLineOption helpOpt("h", QCoreApplication::translate("main", "help"));

    parser.addOption(unpackOpt);
    parser.addOption(packOpt);
    parser.addOption(helpOpt);

    parser.process(app);

    QStringList args = parser.positionalArguments();

    if(parser.isSet(helpOpt))
    {
        printHelp();
        return 0;
    }


    if(args.size()<2||(!parser.isSet(packOpt)&&!parser.isSet(unpackOpt)))
    {
        printHelp();
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
        HtmlExtractor extractor(args[0]);
        extractor.moveTemplates(args[1]);
        if(args.size() > 2)
        {
            extractor.saveTo(args[2]);
        }
        else
        {
            extractor.save();
        }
    }

    return 0;
}
