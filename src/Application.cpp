#include "Application.hpp"

namespace Xeth{

Application::Application(const Settings &settings, int &argc, char **argv):
    _app(argc, argv),
    _facade(settings),
    _window(_facade)
{

}


int Application::exec()
{
    _window.moveToScreenCenter();
    _window.show();
    QObject::connect(&_window, SIGNAL(Closing()), this, SLOT(shutdown()), Qt::DirectConnection);
    return _app.exec();
}


void Application::shutdown()
{
    _facade.shutdown();
    QCoreApplication::exit();
}




}
