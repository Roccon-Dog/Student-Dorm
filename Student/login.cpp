#include "login.h"
#include "ui_login.h"
#include<mainwindow.h>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include<QMessageBox>
#include"usermainwindow.h"
extern QString mynum="";    //声明一个全局变量
login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    this->setWindowTitle("登录");
     connect(ui->lineEdit_2,    //lineEdit_2代表密码输入框
             SIGNAL(returnPressed()),
             ui->login2,        //login2代表登录按钮
             SIGNAL(clicked()),
             Qt::UniqueConnection//防止重复连接。
             );
}

login::~login()
{
    delete ui;
}

void login::on_login2_clicked()//点击登录按钮
{
    bool flag=0;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "Student");//实现数据库连接的操作
     qDebug() << db.connectionName();
    db.setDatabaseName("Studnet.db");
     qDebug() << db.databaseName();

     if (!db.open())//打开数据库时若失败
    {
        qDebug() << "open fail";
        qDebug() << db.lastError().text();

    }

    //打开成功执行sql
    QString sql =
            "create table if not exists student(studentnum varchar(20), name varchar(20),"
            "password varchar(30),room varchar(50),sex varchar(10),"
            "college varchar(20), major varchar(20),come varchar(30),left varchar(30),money varchar(30)"
            ");";
        QSqlQuery query(db);//访问数据库
        if (!query.exec(sql))//若创建表失败
        {
            qDebug() << query.lastError().text();

        }
        qDebug()<<"打开数据库成功"<<endl;
        sql = "select * from student;";  //获取数据库所有用户
           if (!query.exec(sql))
           {
               qDebug() << query.lastError().text();

           }
        while(query.next()) //遍历看是否有相同的学号
        {

            if(query.value(0).toString().compare(ui->lineEdit->text())==0  //若输入的学号与数据库中的学号一致
                    &&
                    query.value(2).toString().compare(ui->lineEdit_2->text())==0   //若输入的密码与数据库中的密码一致
               )
           {
               flag=1;
               mynum=query.value(0).toString();
               break;

           }
        }


    if(flag)    //如果flag不等于0，即学号和密码正确时，进入系统主界面
    {
        this->close();
        userMainWindow *temp=new userMainWindow;
        temp->show();


    }
    else
    {
        QMessageBox::about(this, "登录失败", " 用户名或者密码错误");
    }
}

void login::on_back_clicked()//返回选择登录注册界面
{
    this->close();
    MainWindow *temp=new MainWindow;
    temp->show();

}
