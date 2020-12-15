#include "datedialog.h"
#include "ui_datedialog.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include"usermainwindow.h"
extern QString mynum;
dateDialog::dateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dateDialog)
{
    ui->setupUi(this);
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
        if (!query.exec(sql))//创建表
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
                //将入住时间和离开时间的信息返回到入住离开时间界面中
                  ui->lineEdit->setText(query.value(7).toString());
                  ui->lineEdit_2->setText(query.value(8).toString());

           }



}

dateDialog::~dateDialog()
{
    delete ui;
}

void dateDialog::on_pushButton_clicked()    //点击返回按钮，则返回系统主界面
{
    userMainWindow *temp=new userMainWindow;
    temp->show();
    this->close();
}
