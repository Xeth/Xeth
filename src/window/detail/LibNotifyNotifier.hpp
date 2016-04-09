#pragma once


#if __LIBNOTIFY_ENABLED__

#include <libnotify/notify.h>


namespace Xeth{


class LibNotifyNotifier
{
    public:
        LibNotifyNotifier();
        void showMessage(const QString &title, const QString &message, QSystemTrayIcon::MessageIcon icon, int timeout);

};


}

#endif
