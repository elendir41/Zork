#include "mainwindow.h"
#include "ZorkUL.h"

#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();


    ZorkUL temp;

    temp.play();

    return a.exec();
}
