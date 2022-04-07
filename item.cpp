#include "item.h"
#include "Character.h"

Item::Item (QString name, ObjectType type) {
    this->name = name;
    this->type = type;
}

Item::Item(QString name) {
    this->name = name;
}

Item::~Item()
{
    delete this;
}

ObjectType Item::GetType()
{
    return type;
}



QString Item::GetLongDescription()
{
    return " item(s), " + name + ".\n";
}

void Item::UseItem(int index)
{
    MainWindow::Instance->Print("You can not do anything with  " + name + " like that");
}
