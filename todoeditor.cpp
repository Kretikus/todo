#include "todoeditor.h"
#include "ui_todoeditor.h"

#include <QDir>
#include <QFile>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QStandardPaths>
#include <QTimer>
#include <QUrlQuery>
#include <QSettings>

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
    QSettings settings;
    const auto remotePath = settings.value("remote/todoRemotePath", "").toString();
    const auto remoteFile = settings.value("remote/todoRemoteFilename", "").toString();

    QNetworkRequest req(QUrl(remotePath + "/todo.php"));

    QByteArray data;

    QUrlQuery query;
    query.addQueryItem("filename", remoteFile);
    query.addQueryItem("content", ui->todoEdit->toPlainText());

    QNetworkReply * reply = mgr_.put(req, query.toString().toUtf8());
    while (reply->isRunning()) {
        qApp->processEvents();
    }
    qDebug() << QString::fromLatin1(reply->readAll());
    reply->deleteLater();
}

void ToDoEditor::loadRemote()
{
    QSettings settings;
    const auto remotePath = settings.value("remote/todoRemotePath", "").toString();
    const auto remoteFile = settings.value("remote/todoRemoteFilename", "").toString();

    QNetworkRequest req(QUrl(remotePath + "/" + remoteFile));

    QNetworkReply * reply = mgr_.get(req);
    while (reply->isRunning()) {
        qApp->processEvents();
    }

    const auto text = QString::fromUtf8(reply->readAll());
    qDebug() << text;
    ui->todoEdit->setPlainText(text);
	reply->deleteLater();
}

void ToDoEditor::closeEvent(QCloseEvent *)
{
    onClose();
}

