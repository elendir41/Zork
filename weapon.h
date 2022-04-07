#ifndef WEAPON_H
#define WEAPON_H

#include "item.h"

class Weapon : public Item
{
private:
    const float damage;

public:
    Weapon(QString name, ObjectType type,  float damage);
    float GetDamage();
    virtual QString GetLongDescription();
    virtual void UseItem(int index);
};

#endif // WEAPON_H
