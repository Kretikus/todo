#ifndef TODOEDITOR_H
#define TODOEDITOR_H

#include <QWidget>
#include <QNetworkAccessManager>

namespace Ui {
class ToDoEditor;
}

class ToDoEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ToDoEditor(QWidget *parent = 0);
    ~ToDoEditor();

private Q_SLOTS:
    void onClose();

public Q_SLOTS:
    void showAndRaise();
    void saveRemote();
    void loadRemote();

private:
    Ui::ToDoEditor *ui;
    QNetworkAccessManager mgr_;
};

#endif // TODOEDITOR_H
