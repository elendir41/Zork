#include "Character.h"
#include "ZorkUL.h"
#include "enemy.h"

Character::Character(QString description)
{
	this->description = description;
    if (Instance == nullptr)
    {
        Instance = this;
    }
    nbLives = 4;
    currentWeapon = new Weapon("Fist", ObjectType::weapon, 1);
}

Character::~Character()
{
    inventory.clear();
}

void Character::addItem(Item *item)
{
    inventory.push_back(item);
}


QString Character::shortDescription()
{
    return description;
}

QString Character::longDescription()
{
    QString res = description;
    res += '\n';
    for (size_t i = 0; i < inventory.size(); i++)
    {
        res += inventory[i]->GetName();
        res += "    ";
    }
    return res;
}

void Character::Attack(Enemy *enemy, int index)
{
    float damage = currentWeapon->GetDamage();
    enemy->ReceiveDamage(damage);
    if (enemy->GetLives() <= 0)
    {
        if (enemy->GetType() == EnemyType::Gob)
        {
            delete  (Gobelin*) enemy;
        }

        ZorkUL::Instance->GetCurrentRoom()->enemiesInRoom.erase(ZorkUL::Instance->GetCurrentRoom()->enemiesInRoom.begin() + index);
    }
}

void Character::ChangeWeapon(Weapon *newWeapon)
{
    currentWeapon = newWeapon;
}


void Character::ReceiveDamage(float amount)
{
    nbLives -= amount;
}

float Character::GetLives()
{
    return nbLives;
}

bool Character::IsAlreadyInInventory(Item* item)
{
        for (size_t i = 0; i < inventory.size(); i++)
        {
            if (item->GetName() == inventory[i]->GetName())
            {
                return true;
            }
        }
        return false;
}

void Character::RemoveItem(Item *item)
{
    auto it = find(inventory.begin(), inventory.end(), item);
    inventory.erase(it);
}

Item* Character::GetItem(int index)
{
    return inventory[index];
}

Weapon* Character::GetCurrentWeapon()
{
    return currentWeapon;
}
