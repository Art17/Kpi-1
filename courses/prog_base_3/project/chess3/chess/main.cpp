#include "mainwindow.h"
#include <QApplication>

#include <chessboard.h>
#include <QThread>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap splashImage(":/Images/resources/images/splash.png");
    QSplashScreen splashWindow(splashImage);
    splashWindow.show ();

    MainWindow* pMainWindow = new MainWindow ();

    int windowWidth = 1366;
    int windowHeight = 704;

    pMainWindow->setGeometry(QRect (200, 50, windowWidth, windowHeight));
    pMainWindow->setWindowState(Qt::WindowMaximized);
    pMainWindow->showChessBoard ();

    QThread::sleep (2);
    splashWindow.finish(pMainWindow);
    pMainWindow->show ();


    return a.exec();
}
