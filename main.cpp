#include "databasewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DatabaseWindow w;
    w.show();

    DatabaseWindow dbMode;
    QSqlDatabase database;
    int ret = dbMode.init_connect_datasheet(database);
    qDebug() << ret;
    dbMode.creat_datasheet(database);
    return a.exec();
}
