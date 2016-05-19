#include "infodialog.h"
#include "ui_endgamedialog.h"

InfoDialog::InfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::endgamedialog)
{
    text = "Game ended";
    this->setWindowTitle("Information");
    ui->setupUi(this);
}

InfoDialog::~InfoDialog()
{
    delete ui;
}

void InfoDialog::on_pushButton_clicked()
{
    accept ();
}

void InfoDialog::setText(QString str)
{
    text = str;
    ui->infoLabel->setText(text);
    this->setWindowTitle("Information");
}
