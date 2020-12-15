#include "fixdialog.h"
#include "ui_fixdialog.h"
#include"usermainwindow.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include<QHBoxLayout>
#include<QMessageBox>
extern QString mynum;
fixDialog::fixDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fixDialog)
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
            "create table if not exists fix(studentnum varchar(20),fixrecord varchar(20));";
        QSqlQuery query(db);//访问数据库
        if (!query.exec(sql))//创建表
        {
            qDebug() << query.lastError().text();

        }
        qDebug()<<"打开数据库成功"<<endl;
        sql = "select * from fix where studentnum=";  //获取数据库所有用户
        sql=sql+mynum;
           if (!query.exec(sql))
           {
               qDebug() << query.lastError().text();

           }
         int i=0;
         while(query.next())    //报修信息的格式以及数据库中的信息
         {
             i++;
             QWidget *c=new QWidget(ui->listWidget);
             QHBoxLayout *hl=new QHBoxLayout(c);

             QLabel *ID=new QLabel(mynum);

             QLabel *Date=new QLabel(query.value(1).toString());
             qDebug()<<query.value(1).toString();


             ID->setFixedWidth(120);
             ID->setFixedHeight(40);

            Date->setFixedWidth(120);
             Date->setFixedHeight(40);


             ID->setAlignment(Qt::AlignHCenter);

             Date->setAlignment(Qt::AlignHCenter);

             hl->addWidget(ID);
             hl->addStretch(1);

             hl->addWidget(Date);
             hl->addStretch(1);


             hl->setContentsMargins(3,0,0,3);
             c->setLayout(hl);
             c->resize(350,100);
             c->show();

             QListWidgetItem *item=new QListWidgetItem(ui->listWidget);
             item->setSizeHint(QSize(200,40));  //设置行的大小
             ui->listWidget->setItemWidget(item,c);

         }
         if(i==0)
         {
             ui->label_2->setText("暂无报修信息");
         }

}

fixDialog::~fixDialog()
{
    delete ui;
}

void fixDialog::on_pushButton_clicked() //点击返回按钮，则返回主界面
{
    this->close();
    userMainWindow *temp=new userMainWindow;
    temp->show();
}

void fixDialog::on_pushButton_2_clicked()   //点击报修按钮
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "Student");//加载数据库
     qDebug() << db.connectionName();
    db.setDatabaseName("Studnet.db");
     qDebug() << db.databaseName();

     if (!db.open())//若打开数据库失败
    {
        qDebug() << "open fail";
        qDebug() << db.lastError().text();

    }

    //打开成功执行sql
    QString sql =
            "create table if not exists fix(studentnum varchar(20),fixrecord varchar(20));";
        QSqlQuery query(db);//访问数据库
        if (!query.exec(sql))//若创建表失败
        {
            qDebug() << query.lastError().text();

        }
        qDebug()<<"打开数据库成功"<<endl;
        //将学生学号、报修物品名插入至数据库中
      query.prepare("INSERT INTO fix (studentnum,fixrecord) "
                    "VALUES (:studentnum,:fixrecord)");
      query.bindValue(":studentnum",mynum); //学生学号
      query.bindValue(":fixrecord",ui->lineEdit->text());   //输入的物品名
      query.exec();//入库
      QMessageBox::about(this, "成功", "报修成功");

}
