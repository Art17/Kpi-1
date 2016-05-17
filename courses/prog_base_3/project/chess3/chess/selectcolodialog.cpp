#include "selectcolordialog.h"
#include "ui_selectcolordialog.h"

SelectColorDialog::SelectColorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectColor)
{
    setWindowFlags(windowFlags() ^ Qt::WindowCloseButtonHint);
    ui->setupUi(this);
}

SelectColorDialog::~SelectColorDialog()
{
    delete ui;
}

void SelectColorDialog::on_whiteButton_clicked()
{
    bWhite = true;
    accept ();
}

void SelectColorDialog::on_blackButton_clicked()
{
    bWhite = false;
    accept();
}

bool SelectColorDialog::isWhite ()
{
    return bWhite;
}
