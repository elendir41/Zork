#include "weapon.h"
#include "mainwindow.h"

Weapon::Weapon(QString name, ObjectType type, float damage)
    : Item(name, type), damage(damage)
{
}

float Weapon::GetDamage()
{
    return damage;
}

QString Weapon::GetLongDescription()
{
    return name + " (damage: " + QString::number(damage) + ")";
}

void Weapon::UseItem(int index)
{
    MainWindow::Instance->Print("You can not use it like that");
}
