#ifndef FIXDIALOG_H
#define FIXDIALOG_H

#include <QDialog>

namespace Ui {
class fixDialog;
}

class fixDialog : public QDialog
{
    Q_OBJECT

public:
    explicit fixDialog(QWidget *parent = 0);
    ~fixDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::fixDialog *ui;
};

#endif // FIXDIALOG_H
