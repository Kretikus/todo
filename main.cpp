#include "todoeditor.h"
#include <QApplication>
#include <QMenu>
#include <QSystemTrayIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);

    ToDoEditor w;
    w.setAttribute(Qt::WA_DeleteOnClose, false);

    QSystemTrayIcon trayIcon;
    trayIcon.setIcon(QIcon(":trayicon"));
    a.connect(&trayIcon, &QSystemTrayIcon::activated, &w, &ToDoEditor::showAndRaise);

    QMenu menu;
    QMenu* remoteMenu = menu.addMenu("&Remote");
    remoteMenu->addAction("&Save Remote", &w, SLOT(saveRemote()));
    remoteMenu->addSeparator();
    remoteMenu->addAction("&Load Remote", &w, SLOT(loadRemote()));
    menu.addSeparator();
    menu.addAction("&Beenden", &a, SLOT(quit()));
    trayIcon.setContextMenu(&menu);
    trayIcon.show();

    return a.exec();
}
