#include "key.h"
#include "ZorkUL.h"
#include "inventorywidget.h"

Key::Key(QString name, ObjectType type, Room* lock)
    : Item(name, type)
{
    this->lock = lock;
}

Key::~Key()
{
    MainWindow::Instance->Print("You open the room " + lock->shortDescription());
}

QString Key::GetLongDescription()
{
    return name + " -> " + lock->shortDescription();
}

void Key::UseItem(int index)
{
    map<QString, Room*> exits = ZorkUL::Instance->GetCurrentRoom()->GetExits();
    for (map<QString, Room*>::iterator i = exits.begin(); i != exits.end(); i++)
    {
        if (i->second == lock)
        {
            lock->SetIsLocked(false);
            MainWindow::Instance->Print("You open door " + lock->shortDescription() + " !");
            InventoryWidget::Instance->RemoveItem(index);
            Character::Instance->RemoveItem((Item*)this);
            return;
        }
    }
}
