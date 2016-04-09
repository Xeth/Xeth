#pragma once 

#include <QObject>
#include <cstdlib>

#include "detail/SystemTrayIconInterface.hpp"
#include "detail/UnityTrayIcon.hpp"
#include "detail/GtkTrayIcon.hpp"
#include "detail/QtTrayIcon.hpp"


namespace Xeth{

/*
    tray adapter
*/

class Tray : public QObject
{
    Q_OBJECT
    public:
        Tray(QObject *parent = NULL);
        ~Tray();

        void setContextMenu(QMenu* menu);
        void show();
        void hide();
        void setVisible(bool);
        void setIcon(QIcon &icon);
        void showMessage(const QString &title, const QString &message, QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::Information, int timeout = 10000);

    private:
        SystemTrayIconInterface *_strategy;

};



}
