#include <QCoreApplication>
#include "ZorkUL.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ZorkUL temp;
    temp.play();
    return a.exec();
}
