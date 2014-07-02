#ifndef TODOEDITOR_H
#define TODOEDITOR_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QSystemTrayIcon>

namespace Ui {
class ToDoEditor;
}

class ToDoEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ToDoEditor(QWidget *parent = 0);
    ~ToDoEditor();

    void saveLocal();
    void loadLocal();

private Q_SLOTS:
    void onClose();

public Q_SLOTS:
    void showAndRaise(QSystemTrayIcon::ActivationReason);
    void saveRemote();
    void loadRemote();

protected:
    virtual void closeEvent(QCloseEvent *);

private:
    Ui::ToDoEditor *ui;
    QNetworkAccessManager mgr_;
};

#endif // TODOEDITOR_H
