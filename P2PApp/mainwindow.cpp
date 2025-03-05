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
