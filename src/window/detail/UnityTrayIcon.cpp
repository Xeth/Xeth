#include "UnityTrayIcon.hpp"

#if __UNITY_ENABLED__


namespace Xeth{


UnityTrayIcon::UnityTrayIcon()
{
    gtk_init(NULL, NULL);
    QString path = QCoreApplication::applicationDirPath();
    path.append("/icon/");
    _indicator = app_indicator_new_with_path("ethereum", "ethereum", APP_INDICATOR_CATEGORY_APPLICATION_STATUS, path.toStdString().c_str());
}


UnityTrayIcon::~UnityTrayIcon()
{}


void UnityTrayIcon::setContextMenu(QMenu* menu)
{
    _menu.copy(menu);
    app_indicator_set_menu(_indicator, _menu.getHandle());
}


void UnityTrayIcon::show()
{
    setVisible(true);
}


void UnityTrayIcon::hide()
{
    setVisible(false);
}


void UnityTrayIcon::setVisible(bool visible)
{
    app_indicator_set_status(_indicator, visible ? APP_INDICATOR_STATUS_ACTIVE : APP_INDICATOR_STATUS_PASSIVE);
}


void UnityTrayIcon::showMessage(const QString &title, const QString &message, QSystemTrayIcon::MessageIcon icon, int timeout)
{
#if __LIBNOTIFY_ENABLED__
    _notifier.showMessage(title, message, icon, timeout);
#endif
}


}

#endif
