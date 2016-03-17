#include "JavaScriptMinifier.hpp"

QString MinifyJS::operator()(const QString &content)
{
    QString code = content;
    code.replace("'", "\\'").replace("\n","\\n").replace("\r","\\r");
    QString js = "var minify = function(code){var ast = UglifyJS.parse(code); ast.figure_out_scope(); var compressor = UglifyJS.Compressor();ast = ast.transform(compressor);ast.figure_out_scope();ast.compute_char_frequency();ast.mangle_names();return ast.print_to_string();};minify('";
    js+=code;
    js+="')";

    return _invoker.execute(js).toString();
}
