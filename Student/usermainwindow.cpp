#include "usermainwindow.h"
#include "ui_usermainwindow.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include"login.h"
#include"adddialog.h"
#include"fixdialog.h"
#include"datedialog.h"
extern QString mynum;
userMainWindow::userMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::userMainWindow)
{
    ui->setupUi(this);

      ui->label_2->setStyleSheet("QLabel{"

                               "border-image:url(../student/头像.jpg) 4 4 4 4 stretch stretch;"

                               "}");
      QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "Student");//加载数据库
       qDebug() << db.connectionName();
      db.setDatabaseName("Studnet.db");
       qDebug() << db.databaseName();

       if (!db.open())//打开数据库
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
          sql = "select * from student where studentnum=";  //获取数据库所有用户
          sql=sql+mynum;
             if (!query.exec(sql))
             {
                 qDebug() << query.lastError().text();

             }
             if(query.next()) //遍历看是否有相同的学号
             {
                 //将数据库中水卡余额、学号、姓名、密码、宿舍、性别、学院、专业的信息返回到主界面中
                 ui->label_4->setText("目前卡上余额:"+query.value(9).toString());
                 ui->lineEdit->setText(query.value(0).toString());
                 ui->lineEdit_2->setText(query.value(1).toString());
                 ui->lineEdit_3->setText(query.value(2).toString());
                  ui->lineEdit_5->setText(query.value(3).toString());
                  ui->lineEdit_6->setText(query.value(4).toString());
                   ui->lineEdit_7->setText(query.value(5).toString());
                    ui->lineEdit_8->setText(query.value(6).toString());


             }



}

userMainWindow::~userMainWindow()
{
    delete ui;
}

void userMainWindow::on_pushButton_3_clicked()  //点击余额更新按钮，则弹出水卡余额更新界面
{
     this->close();
    addDialog *temp=new addDialog;
    temp->show();

}

void userMainWindow::on_pushButton_clicked()    //点击查看报修信息按钮，则弹出报修信息界面
{
    this->close();
    fixDialog *temp=new fixDialog;
    temp->show();
}


void userMainWindow::on_pushButton_2_clicked()  //点击退出按钮，则返回登录界面
{
    this->close();
    login *temp=new login;
    temp->show();


}

void userMainWindow::on_pushButton_4_clicked()  //点击查询入住按钮，则弹出查询入住信息界面
{
    this->close();
    dateDialog *temp=new dateDialog;
    temp->show();

}
