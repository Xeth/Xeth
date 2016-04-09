#pragma once 

#include <QMenu>
#include <QSystemTrayIcon>


namespace Xeth{


class SystemTrayIconInterface
{
    public:
        virtual ~SystemTrayIconInterface();
        virtual void setContextMenu(QMenu* menu) = 0;
        virtual void show() = 0;
        virtual void hide() = 0;
        virtual void setVisible(bool) = 0;
        virtual void showMessage(const QString &title, const QString &message, QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::Information, int timeout = 10000) = 0;
};


}
