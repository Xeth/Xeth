#pragma once 

#if __GTK_ENABLED__ || __UNITY_ENABLED__

#include <QString>
#include <QMenu>

#ifdef signals
#undef signals
#endif
extern "C" {
    #include <gtk/gtk.h>
}
#define signals public



namespace Xeth{


class Menu
{
    public:
        Menu();
        ~Menu();

        void copy(QMenu *);
        void add(QAction *);
        ::GtkMenu *getHandle();
        GtkWidget *getWidget();

    private:
        static void CallBack(GtkMenu*, gpointer action);

    private:
        GtkWidget *_handle;
};


}

#endif
