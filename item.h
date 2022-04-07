#ifndef ITEM_H_
#define ITEM_H_

#include <map>
#include <QString>
#include <iostream>
using namespace std;

enum ObjectType
{
    weapon,
    key,
    potion,
    others
};

class Item {
protected:
    QString name;
    QString longDescription;
    ObjectType type;
	int weightGrams;
	float value;

public:
    Item (QString name, ObjectType type);
    Item (QString name);
    virtual ~Item();
    inline QString GetName() {return name;};
    virtual QString GetLongDescription();
    ObjectType GetType();
	void setWeaponCheck(int weaponCheck);
    virtual void UseItem(int index);

    bool operator==(Item* item)
    {
        return this->name == item->GetName();
    }
    bool operator!=(Item* item)
    {
        return this->name != item->GetName();
    }
};

#endif /*ITEM_H_*/
