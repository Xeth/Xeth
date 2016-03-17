#include <QDebug>

#include "lib/CSSMinifier.hpp"

int main(int argc, char **argv)
{

    if(argc<3)
    {
        qDebug()<<"invalid arguments, usage: minifier [inputdir] [outputdir]";
        return 1;
    }

    qDebug()<<"minifying "<<argv[1]<<", output "<<argv[2];


    CSSMinifier minifier;
    minifier.parseDirectory(argv[1], argv[2]);

    return 0;
}
