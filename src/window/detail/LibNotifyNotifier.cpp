#include "LibNotifyNotifier.hpp"
#if __LIBNOTIFY_ENABLED__

namespace Xeth{

LibNotifyNotifier::LibNotifyNotifier()
{
    notify_init("xeth");
}


void LibNotifyNotifier::showMessage(const QString &title, const QString &message, QSystemTrayIcon::MessageIcon icon, int timeout)
{
    NotifyNotification* notification = notify_notification_new(title.toStdString().c_str(), message.toStdString().c_str(),0);
    if(notification)
    {
        notify_notification_set_timeout(notification, timeout);
        notify_notification_show(notification, 0);
    }
}

}

#endif
