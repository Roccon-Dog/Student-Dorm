#include "adddialog.h"
#include "ui_adddialog.h"
#include"usermainwindow.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
extern QString mynum;
addDialog::addDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addDialog)
{
    ui->setupUi(this);

}

addDialog::~addDialog()
{
    delete ui;
}

void addDialog::on_pushButton_clicked()
{
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


        sql="update student set money=";
        sql=sql+ui->lineEdit->text()+" where studentnum="+mynum;    //将输入的金额更新到数据库中
        if(!query.exec(sql))
        {
             qDebug() << query.lastError().text();
        }
        this->close();
        userMainWindow *temp=new userMainWindow;
        temp->show();


}
