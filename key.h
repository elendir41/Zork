#ifndef KEY_H
#define KEY_H

#include "item.h"
#include "Room.h"

class Key: public Item
{
private:
    Room* lock;

public:
    Key(QString name, ObjectType type, Room* lock);
    ~Key();
    virtual QString GetLongDescription();
    virtual void UseItem(int index);


};

#endif // KEY_H
