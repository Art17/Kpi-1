#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "chessboard.h"
#include "aboutdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    void loadBackground ();

    void showChessBoard ();

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_actionAbout_Qt_triggered();

    void on_actionUndo_triggered();

    void on_actionNew_game_against_human_triggered();

    void on_actionNew_game_against_computer_triggered();

    void on_actionAboutChess_triggered();

private:
    Ui::MainWindow *ui;

    ChessBoard* pChessBoard;
};

#endif // MAINWINDOW_H
