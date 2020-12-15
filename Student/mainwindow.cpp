#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<login.h>
#include<signin.h>
#include<QDebug>

//选择登录注册界面
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),//载入Qt架构，调用MainWindow
    ui(new Ui::MainWindow)
{
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    ui->setupUi(this);//此处ui指系统根据界面文件自动生成的ui类创建的对象
    this->setWindowTitle("宿舍管理系统"); //标题
}

MainWindow::~MainWindow()
{
    delete ui;//析构的时候delete掉ui
}


void MainWindow::on_login_clicked()//定义登录按钮的方法，点击登录按钮进入登录界面
{
    login *temp=new login;
    temp->show();
    this->close();
}

void MainWindow::on_signin_clicked()//定义注册按钮的方法，点击注册按钮进入注册界面
{
    signin *temp=new signin;
    temp->show();
    this->close();
}
