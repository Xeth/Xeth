#include <QWebView>
#include <QApplication>
#include <QTextStream>
#include <QDirIterator>
#include <QFile>
#include <QFileInfo>
#include <QDebug>

#include "lib/UnderscoreCompiler.hpp"

int main(int argc, char **argv)
{

    if(argc<3)
    {
        qDebug()<<"invalid arguments, usage: compile [inputdir] [outputdir]";
        return 1;
    }

    qDebug()<<"compiling "<<argv[1]<<", output "<<argv[2];

    QApplication app(argc, argv);

    UnderscoreCompiler compiler;
    compiler.parseDirectory(argv[1], argv[2]);

//    return app.exec();

    return 0;
}
