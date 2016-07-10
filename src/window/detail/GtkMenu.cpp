#include "GtkMenu.hpp"

#if __GTK_ENABLED__ || __UNITY_ENABLED__

namespace Xeth{


Menu::Menu()
{
    _handle = gtk_menu_new();
}


Menu::~Menu()
{}


void Menu::CallBack(GtkMenu*, gpointer action)
{
    ((QAction*)action)->activate(QAction::Trigger);
}


void Menu::copy(QMenu *menu)
{
    QList<QAction *> actions = menu->actions();
    for (QList<QAction *>::iterator it = actions.begin(), end = actions.end(); it!=end; ++it)
    {
        add(*it);
    }
}


void Menu::add(QAction *action)
{
    QString text = action->text().replace('&',"");

    GtkWidget* item;
    if (action->isSeparator())
    {
        item = gtk_menu_item_new();
    }
    else
    {
        item = gtk_menu_item_new_with_label(text.toStdString().c_str());
    }
    gtk_menu_shell_append(GTK_MENU_SHELL(_handle), item);
    g_signal_connect(item, "activate", G_CALLBACK(&Menu::CallBack), action);
    gtk_widget_show(item);
}


::GtkMenu * Menu::getHandle()
{
    return GTK_MENU(_handle);
}


GtkWidget * Menu::getWidget()
{
    return _handle;
}


}

#endif
