#include "Application.hpp"

namespace Xeth{

Application::Application(const Settings &settings, int &argc, char **argv):
    _app(argc, argv),
    _facade(settings),
    _contextBuilder(_facade),
    _window(_contextBuilder)
{}


int Application::exec()
{
    _window.moveToScreenCenter();
    _window.show();
    return _app.exec();
}




}
