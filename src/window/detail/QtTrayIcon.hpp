#pragma once


#include <QSystemTrayIcon>
#include <QMenu>

#include "SystemTrayIconInterface.hpp"


namespace Xeth{


class QtTrayIcon : public QSystemTrayIcon,  public SystemTrayIconInterface
{
    public:
        QtTrayIcon();

        void setContextMenu(QMenu* menu);
        void show();
        void hide();
        void setVisible(bool);
        void showMessage(const QString &title, const QString &message, QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::Information, int timeout = 10000);

};


}
