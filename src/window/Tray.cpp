#include "Tray.hpp"
#include <QDebug>

namespace Xeth{


Tray::Tray(QObject *parent) : QObject(parent)
{
    QString desktop = getenv("XDG_CURRENT_DESKTOP");
    if (desktop.isEmpty())
    {
        desktop = getenv("DESKTOP_SESSION");
    }
    desktop = desktop.toLower();

    #ifdef __UNITY_ENABLED__
    if (desktop == "unity")
    {
        qDebug()<<"starting unity strategy";
        _strategy = new UnityTrayIcon();
    }
    else
    #endif
    #ifdef __GTK_ENABLED__
    if (desktop == "xfce" || desktop.contains("gnome") || desktop == "mate" || desktop == "x-cinnamon")
    {
        qDebug()<<"starting gtk strategy";
        _strategy = new GtkTrayIcon();
    }
    else
    #endif
    {
        qDebug()<<"starting qt strategy";
        _strategy = new QtTrayIcon();
    }
}

Tray::~Tray()
{
    delete _strategy;
}


void Tray::setContextMenu(QMenu* menu)
{
    _strategy->setContextMenu(menu);
}


void Tray::show()
{
    _strategy->show();
}


void Tray::hide()
{
    _strategy->hide();
}


void Tray::setVisible(bool visible)
{
    _strategy->setVisible(visible);
}


void Tray::showMessage(const QString &title, const QString &message, QSystemTrayIcon::MessageIcon icon, int timeout)
{
    _strategy->showMessage(title, message, icon, timeout);
}


}
