#ifndef SELECTFIGUREDIALOG_H
#define SELECTFIGUREDIALOG_H

#include <QDialog>
#include <figures.h>

namespace Ui {
class SelectFigureDialog;
}

class SelectFigureDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectFigureDialog(QWidget *parent = 0);
    ~SelectFigureDialog();
    int getEnteredValue ();


private slots:
    void on_queenButton_clicked();

    void on_rookButton_clicked();

    void on_knightButton_clicked();

    void on_bishopButton_clicked();

private:
    Ui::SelectFigureDialog *ui;
    int value;
};

#endif // SELECTFIGUREDIALOG_H
