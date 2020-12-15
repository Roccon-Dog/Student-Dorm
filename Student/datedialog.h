#ifndef DATEDIALOG_H
#define DATEDIALOG_H

#include <QDialog>

namespace Ui {
class dateDialog;
}

class dateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit dateDialog(QWidget *parent = 0);
    ~dateDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::dateDialog *ui;
};

#endif // DATEDIALOG_H
