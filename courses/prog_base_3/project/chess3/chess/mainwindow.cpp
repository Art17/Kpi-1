#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    loadBackground ();

    ui->setupUi(this);
}

void MainWindow::showChessBoard()
{
    int windowWidth = this->size().width();
    int windowHeight = this->size().height ();

    pChessBoard = new ChessBoard(this, QPoint((windowWidth - windowHeight)/2, 20), QSize(windowHeight - 18, windowHeight - 18));
    pChessBoard->show ();
}

void MainWindow::loadBackground ()
{
    QPixmap bkgnd(":/Images/resources/images/background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit ();
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt (0, "Qt");
}

void MainWindow::on_actionUndo_triggered()
{
    pChessBoard->undo ();
}

void MainWindow::on_actionNew_game_against_human_triggered()
{
    pChessBoard->newGameAgainstHuman ();
}

void MainWindow::on_actionNew_game_against_computer_triggered()
{
    pChessBoard->newGameAgainstComputer ();
}
