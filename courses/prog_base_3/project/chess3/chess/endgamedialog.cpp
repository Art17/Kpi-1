#include "endgamedialog.h"
#include "ui_endgamedialog.h"

EndGameDialog::EndGameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::endgamedialog)
{
    text = "Game ended";
    ui->setupUi(this);
}

EndGameDialog::~EndGameDialog()
{
    delete ui;
}

void EndGameDialog::on_pushButton_clicked()
{
    accept ();
}

void EndGameDialog::setText(QString str)
{
    text = str;
    ui->infoLabel->setText(text);
}
