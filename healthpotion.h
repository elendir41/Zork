#ifndef HEALTHPOTION_H
#define HEALTHPOTION_H

#include "item.h"


class HealthPotion : public Item
{
private:
    float hp;
public:
    HealthPotion(QString name, ObjectType type, float hp);
    HealthPotion(const HealthPotion &p);
    virtual void UseItem(int index);
};

#endif // HEALTHPOTION_H
