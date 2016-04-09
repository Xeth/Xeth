#include "GtkTrayIcon.hpp"

#if __GTK_ENABLED__


namespace Xeth{


GtkTrayIcon::GtkTrayIcon()
{
    gtk_init(NULL, NULL);
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_resource("/icon/ethereum.png", NULL);
    _icon = gtk_status_icon_new_from_pixbuf(pixbuf);
    g_object_unref(pixbuf);
}


GtkTrayIcon::~GtkTrayIcon()
{}


void GtkTrayIcon::setContextMenu(QMenu* menu)
{
    _menu.copy(menu);
    g_signal_connect(_icon, "popup-menu", G_CALLBACK(&MenuCallBack), this);
}


void GtkTrayIcon::MenuCallBack(GtkMenu*, gint, gint, gpointer data)
{
    gtk_widget_show_all(((GtkTrayIcon*)data)->_menu.getWidget());
    gtk_menu_popup(((GtkTrayIcon*)data)->_menu.getHandle(), 0, 0, 0, 0, 3, gtk_get_current_event_time());

}


void GtkTrayIcon::show()
{
    setVisible(true);
}


void GtkTrayIcon::hide()
{
    setVisible(false);
}


void GtkTrayIcon::setVisible(bool visible)
{
    gtk_status_icon_set_visible(_icon, visible);
}


void GtkTrayIcon::showMessage(const QString &title, const QString &message, QSystemTrayIcon::MessageIcon icon, int timeout)
{
#if __LIBNOTIFY_ENABLED__
    _notifier.showMessage(title, message, icon, timeout);
#endif
}

}

#endif
