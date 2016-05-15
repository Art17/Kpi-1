#include "selectfiguredialog.h"
#include "ui_selectfiguredialog.h"

#include <chessboard.h>

SelectFigureDialog::SelectFigureDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectFigureDialog)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() ^ Qt::WindowCloseButtonHint);
}

SelectFigureDialog::~SelectFigureDialog()
{
    delete ui;
}

int SelectFigureDialog::getEnteredValue()
{
    return value;
}

void SelectFigureDialog::on_queenButton_clicked()
{
    value = Queen;
    accept();
}

void SelectFigureDialog::on_rookButton_clicked()
{
    value = Rook;
    accept();
}

void SelectFigureDialog::on_knightButton_clicked()
{
    value = Knight;
    accept();
}

void SelectFigureDialog::on_bishopButton_clicked()
{
    value = Bishop;
    accept();
}
