#include "mainwindow.h"
#include <QApplication>

#include <chessboard.h>
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* pMainWindow = new MainWindow ();

    int windowWidth = 1366;
    int windowHeight = 704;

    pMainWindow->setGeometry(QRect (200, 50, windowWidth, windowHeight));
    pMainWindow->setWindowState(Qt::WindowMaximized);
    pMainWindow->showChessBoard ();

    pMainWindow->show ();

    return a.exec();
}
