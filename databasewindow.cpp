#include <QString>
#include "databasewindow.h"
#include "ui_databasewindow.h"

DatabaseWindow::DatabaseWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DatabaseWindow)
{
    ui->setupUi(this);
}

int DatabaseWindow::init_connect_datasheet(QSqlDatabase db)
{
    db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("localhost");
    db.setDatabaseName("linbx");
    db.setUserName("root");
    db.setPassword("YES");   //这里输入你的密码

    if (!db.open())
    {
        QMessageBox::critical(0, QObject::tr("无法打开数据库"),"无法创建数据库连接！ ", QMessageBox::Cancel);
        return -1;
    }
    else
    {
        myDebug("init_connect_datasheet ", "ok!");
    }
}

void DatabaseWindow::creat_datasheet(QSqlDatabase db)
{
    //如果 MySQL 数据库中已经存在同名的表， 那么下面的代码不会执行
    QSqlQuery query(db);
    //使数据库支持中文
    //query.exec("SET NAMES 'utf8'");

    //创建 course 表
    query.exec("   CREATE TABLE `linbx`.`sdv`  (\
                   id int primary key,\
                   `xueke` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,\
                   `info` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL\
                    ) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;\
                ");


    query.exec("insert into sdv values(0, 'shuxue', '拎包')");
    query.exec("insert into sdv values(1, 'yingyu', '111')");
    query.exec("insert into sdv values(2, 'jisuanji', '22')");
}

void DatabaseWindow::close_datasheet(QSqlDatabase db)
{
    if(db.open())
    {
        db.close();
    }
}





DatabaseWindow::~DatabaseWindow()
{
    delete ui;
}

void DatabaseWindow::on_pushButton_show_clicked()
{
    QString id_value = ui->lineEdit_id->text();
    QString exec_value = QString("select *from sdv where id = '%1'").arg(id_value);
    myDebug("id_value", id_value);
    myDebug("exec_value", exec_value);

    QSqlQuery query;
    query.exec(exec_value);
    QString id;
    QString xueke;
    QString info;

    while (query.next())
    {
       id = query.value(0).toString();
       xueke = query.value(1).toString();
       info =  query.value(2).toString();
    }

    myDebug("id", id);
    myDebug("xueke", xueke);
    myDebug("info", info);


    QString all_info = "id:      " + id + "\nxueke:" + xueke + "\ninfo:   " + info;
    ui->listWidget->clear();

    ui->listWidget->addItem(all_info);

}

void DatabaseWindow::on_pushButton_insert_clicked()
{
    //从界面获取我们需要的信息
    QString update_id = ui->lineEdit_id->text();
    QString update_xueke = ui->lineEdit_xueke->text();
    QString update_info = ui->lineEdit_info->text();

    if(update_id == "" || update_xueke == "" || update_info == "") //插入信息的时候需要输入完整的信息
    {
       QMessageBox::information(NULL,"Error","请输入完整的信息");
    }
    else
    {
       QString str = QString("insert sdv(id, xueke, info) values(%1, '%2', '%3')").arg(update_id).arg(update_xueke).arg(update_info);
       QSqlQuery query;
       myDebug("query:",str);
       query.exec(str); //执行插入操作
       ui->lineEdit_id->clear();
       ui->lineEdit_xueke->clear();
       ui->lineEdit_info->clear();
       ui->listWidget->clear();
       ui->listWidget->addItem("插入成功");
       query.exec("commit");
    }

}

void DatabaseWindow::on_pushButton_del_clicked()
{
    //从界面获取我们需要的信息
    QString update_id = ui->lineEdit_id->text();

    if(update_id ==  NULL)
    {
        ui->listWidget->clear();
        ui->listWidget->addItem("请输入需要删除的ID");
    }
    else
    {

        //从数据库中查询是否有这ID
        QSqlQuery query;
        QString delete_id_value;
        QString temp = QString("select * from sdv where id = '%1'").arg(update_id);
        myDebug("query", temp);
        query.exec(temp);
        while (query.next())
        {
            delete_id_value = query.value(1).toString();
        }

        if(delete_id_value == NULL)
        {
           QString a = QString("没有ID为%1，删除失败").arg(update_id);
           ui->listWidget->clear();
           ui->listWidget->addItem(a);

           ui->lineEdit_id->clear();
           ui->lineEdit_xueke->clear();
           ui->lineEdit_info->clear();
        }
        else
        {
           QString str =  QString("delete from sdv where id = '%1'").arg(update_id);
           myDebug("query", str);

           query.exec(str);//删除信息
           ui->lineEdit_id->clear();
           ui->lineEdit_xueke->clear();
           ui->lineEdit_info->clear();
           ui->listWidget->clear();
           ui->listWidget->addItem("删除成功");

        }
        query.exec("commit");
    }

}

void DatabaseWindow::on_pushButton_modify_clicked()
{
    //从界面获取我们需要的信息
    QString update_id = ui->lineEdit_id->text();
    QString update_xueke = ui->lineEdit_xueke->text();
    QString update_info = ui->lineEdit_info->text();

    if(update_id == "" || update_xueke == "" || update_info == "") //插入信息的时候需要输入完整的信息
    {
       QMessageBox::information(NULL,"警告","请输入需要修改的人的学号，姓名以及成绩");
    }
    else
    {
        QString temp = QString("select * from sdv where id = '%1'").arg(update_id);
        QSqlQuery query;
        myDebug("query", temp);
        query.exec(temp);// 查询信息
        QString a;
        while (query.next())
        {
            a = query.value(1).toString();
        }

        if(a == NULL)
        {
            QString b = QString("没有名叫%1的人，修改失败").arg(update_id);
            ui->listWidget->clear();
            ui->listWidget->addItem(b);

            ui->lineEdit_id->clear();
            ui->lineEdit_xueke->clear();
            ui->lineEdit_info->clear();
        }
        else
        {
            temp = QString("update sdv set xueke = '%1' , info = '%2' where id = '%3'").arg(update_xueke).arg(update_info).arg(update_id);
            myDebug("query", temp);
            query.exec(temp);
            ui->listWidget->clear();
            ui->listWidget->addItem("Update成功");
            ui->lineEdit_id->clear();
            ui->lineEdit_xueke->clear();
            ui->lineEdit_info->clear();
        }
        query.exec("commit");


    }

}
