#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "networkcontroller.h"

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>

#include <QStyle>
#include <QHostAddress>
#include <QMetaEnum>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void attachFileAction();

private slots:
    void on_lnIPAddress_textChanged(const QString &arg1);

    void on_btnConnect_clicked();

    void network_connected();
    void network_disconnected();
    void netwowork_stateChanged(QAbstractSocket::SocketState);
    void network_errorOccurred(QAbstractSocket::SocketError);

private:
    Ui::MainWindow *ui;
    NetworkController _controller;

    // Methods
    void setNetworkController();
};
#endif // MAINWINDOW_H
