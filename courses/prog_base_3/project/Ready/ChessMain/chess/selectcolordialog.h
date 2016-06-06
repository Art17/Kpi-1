#ifndef SELECTCOLOR_H
#define SELECTCOLOR_H

#include <QDialog>

namespace Ui {
class SelectColor;
}

class SelectColorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectColorDialog(QWidget *parent = 0);
    ~SelectColorDialog();

    bool isWhite ();

private slots:
    void on_whiteButton_clicked();

    void on_blackButton_clicked();

private:
    Ui::SelectColor *ui;

    bool bWhite;
};

#endif // SELECTCOLOR_H
