#pragma once 

#if __GTK_ENABLED__

#include <QMenu>

#include "SystemTrayIconInterface.hpp"
#include "GtkMenu.hpp"
#include "LibNotifyNotifier.hpp"


namespace Xeth{



class GtkTrayIcon : public SystemTrayIconInterface
{
    public:
        GtkTrayIcon();
        ~GtkTrayIcon();

        void setContextMenu(QMenu* menu);
        void show();
        void hide();
        void setVisible(bool);
        void showMessage(const QString &title, const QString &message, QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::Information, int timeout = 10000);

    private:
        static void MenuCallBack(GtkMenu*, gint, gint, gpointer data);

    private:
        GtkStatusIcon* _icon;
        Menu _menu;
#if __LIBNOTIFY_ENABLED__
        LibNotifyNotifier _notifier;
#endif
};



}

#endif
