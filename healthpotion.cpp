#include "healthpotion.h"
#include "inventorywidget.h"
#include "Character.h"

HealthPotion::HealthPotion(QString name, ObjectType type, float hp)
    :Item(name, type)
{
    this->hp = hp;
}

HealthPotion::HealthPotion(const HealthPotion &p)
    : Item(p.name, p.type)
{
    this->hp = p.hp;
}


void HealthPotion::UseItem(int index)
{
    Character::Instance->ReceiveDamage(-hp);
    InventoryWidget::Instance->RemoveItem(index);
    Character::Instance->RemoveItem((Item*)this);
}
