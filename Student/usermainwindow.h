#ifndef USERMAINWINDOW_H
#define USERMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class userMainWindow;
}

class userMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit userMainWindow(QWidget *parent = 0);
    ~userMainWindow();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::userMainWindow *ui;
};

#endif // USERMAINWINDOW_H
