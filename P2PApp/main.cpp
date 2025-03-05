#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("P2P");
    w.setWindowIcon(QIcon(":/Resources/P2PIcon.png"));
    w.show();
    return a.exec();
}
