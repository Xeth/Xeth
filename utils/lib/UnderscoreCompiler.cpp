#include "UnderscoreCompiler.hpp"


QString UnderscoreParser::operator()(const QString &content)
{
    QString input = content;
    input.replace("'", "\\'").replace("\n"," ").replace("\r"," ");
    QString js = "_.template('";
    js += input;
    js += "').source;";
    return _invoker.execute(js).toString();
}


