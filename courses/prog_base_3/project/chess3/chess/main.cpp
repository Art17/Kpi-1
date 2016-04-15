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

    ChessBoard* pChessBoard = new ChessBoard(pMainWindow, QPoint((windowWidth - windowHeight)/2, 20), QSize(windowHeight - 18, windowHeight - 18));

    pMainWindow->show ();
    pChessBoard->show ();

    return a.exec();
}
