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
