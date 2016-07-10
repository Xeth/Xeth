#pragma once 

#if __UNITY_ENABLED__

#include <QString>
#include <QMenu>
#include <QCoreApplication>

#ifdef signals
#undef signals
#endif
extern "C" {
    #include <libappindicator/app-indicator.h>
}
#define signals public

#include "SystemTrayIconInterface.hpp"
#include "GtkMenu.hpp"
#include "LibNotifyNotifier.hpp"

namespace Xeth{


class UnityTrayIcon : public SystemTrayIconInterface
{
    public:
        UnityTrayIcon();
        ~UnityTrayIcon();

        void setContextMenu(QMenu* menu);
        void show();
        void hide();
        void setVisible(bool);
        void showMessage(const QString &title, const QString &message, QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::Information, int timeout = 10000);

    private:
        AppIndicator *_indicator;
        Menu _menu;
#if __LIBNOTIFY_ENABLED__
        LibNotifyNotifier _notifier;
#endif
};



}

#endif
