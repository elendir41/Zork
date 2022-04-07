#ifndef GOBELIN_H
#define GOBELIN_H

#include "enemy.h"

class Gobelin : public Enemy
{
private:

public:
    Gobelin(float HP, QString name, EnemyType type, float damage);
    virtual ~Gobelin();
    virtual void PrintInfo();
    virtual QString getShortDescription();
};

#endif // GOBELIN_H
