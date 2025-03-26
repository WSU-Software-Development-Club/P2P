#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    // Create Open action
    QAction *attachFileAction = new QAction(tr("&Attach File"), this);
    attachFileAction->setShortcut(QKeySequence("Ctrl+A")); // Ctrl+A shortcut
    connect(attachFileAction, &QAction::triggered, this, &MainWindow::attachFileAction);  // Connect the action to a function
    fileMenu->addAction(attachFileAction);  // Add action to File menu

}

void MainWindow::attachFileAction()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open File", QDir::homePath(), "All Files (*.*)");
    qDebug() << "File path " << filePath << "loaded";
    //store this in a message class or something

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lnIPAddress_textChanged(const QString &arg1)
{
    QString state = "0";
    if (arg1 == "...") {
        state = "";
    } else {
        QHostAddress address(arg1);
        if (QAbstractSocket::IPv4Protocol == address.protocol()) {
            state = "1";
        }
    }
    ui->lnIPAddress->setProperty("state", state);
    style()->polish(ui->lnIPAddress);
}


void MainWindow::on_btnConnect_clicked()
{
    auto ip = ui->lnIPAddress->text();
    auto port = ui->spinPort->value();
    _controller.connectToNetwork(ip, port);
}

void MainWindow::network_connected()
{
    ui->lstConsole->addItem("Connected to Network");
}

void MainWindow::network_disconnected()
{
    ui->lstConsole->addItem("Disconnected to Network");
}

void MainWindow::netwowork_stateChanged(QAbstractSocket::SocketState state)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    ui->lstConsole->addItem(metaEnum.valueToKey(state));
}

void MainWindow::network_errorOccurred(QAbstractSocket::SocketError error)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    ui->lstConsole->addItem(metaEnum.valueToKey(error));
}

void MainWindow::setNetworkController()
{

}

