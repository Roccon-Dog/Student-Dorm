#include "signin.h"
#include "ui_signin.h"
#include<mainwindow.h>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include<QMessageBox>

signin::signin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::signin)
{
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    ui->setupUi(this);
    this->setWindowTitle("注册");
    //连接数据库sql
     connect(ui->lineEdit_4,    //lineEdit_4代表再次输入密码编辑框
             SIGNAL(returnPressed()),   //检测两次密码是否一致
             ui->signin2,       //signin2代表注册按钮
             SIGNAL(clicked()),    //点击注册按钮
             Qt::UniqueConnection   //防止重复连接。如果当前信号和槽已经连接过了，就不再连接了
             );

}

signin::~signin()
{
    delete ui;
}

void signin::on_back_clicked()//点击返回按钮，返回主界面
{
    MainWindow *temp=new MainWindow;
    temp->show();
    this->close();
}

void signin::on_signin2_clicked()//点击注册按钮，执行注册按键
{
    bool flag=1;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "Student");//实现数据库连接的操作
    qDebug() << db.connectionName();
    db.setDatabaseName("Studnet.db");   //建立数据库名为“Studnet.db”
     qDebug() << db.databaseName();

     if (!db.open())//打开数据库时若失败
    {
        qDebug() << "open fail";    //输出提示"open fail"
        qDebug() << db.lastError().text();  //反馈错误信息

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
            qDebug() << query.lastError().text();//反馈错误信息

        }
        qDebug()<<"打开数据库成功"<<endl;
        sql = "select * from student;";  //获取数据库所有用户
           if (!query.exec(sql))
           {
               qDebug() << query.lastError().text();//反馈错误信息

           }
        while(query.next()) //遍历看是否有相同的学号
        {

            if(query.value(0).toString().compare(ui->lineEdit->text())==0)  //若学号已被占用
            {
                flag=0;//将bool函数flag的值改为0
                QMessageBox::about(this, "失败", "该学号已被使用");  //弹出提示

            }
        }

        if(flag)    //如果flag不等于0，即学号没被占用
        {
            if(ui->lineEdit_3->text().compare(ui->lineEdit_4->text())==0)   //若两次输入密码一致
            {

                query.prepare("INSERT INTO student (studentnum,name,password,room,sex,college,major,come,left,money) "
                              "VALUES (:studentnum,:name,:password,:room,:sex,:college,:major,:come,:left,:money)");
                //将注册界面输入的信息输入至数据库Student中
                query.bindValue(":studentnum",ui->lineEdit->text());
                query.bindValue(":name",ui->lineEdit_2->text());
                query.bindValue(":password",ui->lineEdit_3->text());
                query.bindValue(":room",ui->lineEdit_5->text());
                query.bindValue(":sex",ui->lineEdit_6->text());
                query.bindValue(":college",ui->lineEdit_7->text());
                query.bindValue(":major",ui->lineEdit_8->text());
                query.bindValue(":come",ui->lineEdit_9->text());
                query.bindValue(":left",ui->lineEdit_10->text());
                query.bindValue(":money",0);

                query.exec();//入库
                QMessageBox::about(this, "成功", " 注册成功");
                ui->back->clicked();    //自动点击返回按钮，返回至选择登录注册界面
            }
            else    //若两次输入的密码不一致
            {
                 QMessageBox::about(this, "失败", "两次密码输入不一致");
            }

        }

}
