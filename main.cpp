#include <QCoreApplication>
#include "esc.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Esc esc;
    esc.start();
    return a.exec();
}
