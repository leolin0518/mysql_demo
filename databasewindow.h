#ifndef DATABASEWINDOW_H
#define DATABASEWINDOW_H

#include <QWidget>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QString>
#include <QtSql/QSqlQuery>
#include <QtSql/QSql>
#include <QDebug>
#define myDebug(x,y)      (qDebug()    << "[Debug "    << __FILE__ << ","  << __FUNCTION__ << "," << __LINE__ << "]:" << x  << y)

namespace Ui {
class DatabaseWindow;
}

class DatabaseWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DatabaseWindow(QWidget *parent = nullptr);
    int init_connect_datasheet(QSqlDatabase db);
    void creat_datasheet(QSqlDatabase db);
    void close_datasheet(QSqlDatabase db);
    ~DatabaseWindow();

private slots:
    void on_pushButton_show_clicked();

    void on_pushButton_insert_clicked();

    void on_pushButton_del_clicked();

    void on_pushButton_modify_clicked();

private:
    Ui::DatabaseWindow *ui;
    DatabaseWindow *model;
    QString mID;

};

#endif // DATABASEWINDOW_H
