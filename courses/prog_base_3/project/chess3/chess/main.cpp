#include "mainwindow.h"
#include <QApplication>

#include <chessboard.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* pMainWindow = new MainWindow ();

    int windowWidth = 1024;
    int windowHeight = 640;

    pMainWindow->setGeometry(QRect (200, 50, windowWidth, windowHeight));
    pMainWindow->showChessBoard ();

    pMainWindow->show ();

    return a.exec();
}
