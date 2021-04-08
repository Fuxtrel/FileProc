#include <QCoreApplication>
#include "client.h"
#include "global.h"
#include <QTextStream>



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString path= a.applicationDirPath();
    Client client(argv, path);
    return a.exec();
}
