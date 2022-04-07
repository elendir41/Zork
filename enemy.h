#ifndef ENEMY_H
#define ENEMY_H

#include <QString>

enum EnemyType
{
    Gob,
    Others
};


class Enemy
{
protected:
    float nbLives;
    float damage;
    EnemyType type;
    QString name;


public:
    Enemy(QString name, float damage);
    virtual ~Enemy();

    EnemyType GetType();
    void ReceiveDamage(float amount);
    void Attack();

    float GetLives();
    virtual QString getShortDescription();
    virtual void PrintInfo() = 0;
};

#endif // ENEMY_H
