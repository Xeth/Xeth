#include "QtTrayIcon.hpp"


namespace Xeth{


QtTrayIcon::QtTrayIcon()
{
    setIcon(QIcon(":/icon/ethereum.ico"));
}

void QtTrayIcon::setContextMenu(QMenu* menu)
{
    QSystemTrayIcon::setContextMenu(menu);
}

void QtTrayIcon::show()
{
    QSystemTrayIcon::show();
}

void QtTrayIcon::hide()
{
    QSystemTrayIcon::hide();
}


void QtTrayIcon::setVisible(bool visible)
{
    QSystemTrayIcon::setVisible(visible);
}

void QtTrayIcon::showMessage(const QString &title, const QString &message, QSystemTrayIcon::MessageIcon icon, int timeout)
{
    QSystemTrayIcon::showMessage(title, message, icon, timeout);
}

}
