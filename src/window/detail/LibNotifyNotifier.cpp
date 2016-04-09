#include "LibNotifyNotifier.hpp"

#if __LIBNOTIFY_ENABLED__


LibNotifyNotifier::LibNotifyNotifier()
{
    notify_init("");
}


bool LibNotifyNotifier::showMessage(const QString &title, const QString &message, QSystemTrayIcon::MessageIcon icon, int timeout);
{
    NotifyNotification* notification = notify_notification_new(title.toStdString().c_str(), message.toStdString().c_str(),0);
    notify_notification_set_timeout(n, timeout);
    return notify_notification_show(n, 0); 
}

#endif
