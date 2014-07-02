#include "todoeditor.h"
#include "ui_todoeditor.h"

#include <QDir>
#include <QFile>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QStandardPaths>
#include <QTimer>
#include <QUrlQuery>

QSharedPointer<QFile> getTodoFile(bool openReadOnly = true)
{
    const auto path = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    QSharedPointer<QFile> file(new QFile(path[0] + QDir::separator() + "ToDo.txt"));
    file->open(openReadOnly ? QIODevice::Text|QIODevice::ReadOnly : QIODevice::Text|QIODevice::ReadWrite);
    return file;
}

ToDoEditor::ToDoEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToDoEditor)
{
    ui->setupUi(this);

    auto file = getTodoFile();
    ui->todoEdit->setPlainText(QString::fromUtf8(file->readAll()));
}

ToDoEditor::~ToDoEditor()
{
    onClose();
    delete ui;
}

void ToDoEditor::onClose()
{
    auto file = getTodoFile(false);
    file->resize(0);
    const auto plainText = ui->todoEdit->toPlainText();
    file->write(plainText.toUtf8());

}

void ToDoEditor::showAndRaise()
{
    activateWindow();
    show();
}

void ToDoEditor::saveRemote()
{
    QNetworkRequest req(QUrl(""));

    QByteArray data;

    QUrlQuery query;
    query.addQueryItem("filename", "todo.txt");
    query.addQueryItem("content", ui->todoEdit->toPlainText());

    QNetworkReply * reply = mgr_.put(req, query.toString().toUtf8());
    while (reply->isRunning()) {
        qApp->processEvents();
    }
    qDebug() << QString::fromLatin1(reply->readAll());
}

void ToDoEditor::loadRemote()
{
    QNetworkRequest req(QUrl(""));

    QNetworkReply * reply = mgr_.get(req);
    while (reply->isRunning()) {
        qApp->processEvents();
    }

    const auto text = QString::fromUtf8(reply->readAll());
    qDebug() << text;
    ui->todoEdit->setPlainText(text);
}

