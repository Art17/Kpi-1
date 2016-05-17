#ifndef ENDGAMEDIALOG_H
#define ENDGAMEDIALOG_H

#include <QDialog>

namespace Ui {
class endgamedialog;
}

class EndGameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EndGameDialog(QWidget *parent = 0);
    ~EndGameDialog();

    void setText (QString);

private slots:
    void on_pushButton_clicked();

private:
    Ui::endgamedialog *ui;

    QString text;
};

#endif // ENDGAMEDIALOG_H
