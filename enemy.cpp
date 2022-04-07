#include "enemy.h"
#include "mainwindow.h"
#include "Character.h"

Enemy::Enemy(QString name, float damage)
{
    this->damage = damage;
    this->name = name;
}

Enemy::~Enemy()
{
}

float Enemy::GetLives()
{
    return nbLives;
}

void Enemy::ReceiveDamage(float amount)
{
    nbLives -= amount;
}


void Enemy::PrintInfo()
{
    QString message = "The enemy has " + QString::number( nbLives) + " healthpoints";
    MainWindow::Instance->Print(message);
}

QString Enemy::getShortDescription()
{
    return "Enemy";
}

EnemyType Enemy::GetType()
{
    return type;
}

void Enemy::Attack()
{
    Character::Instance->ReceiveDamage(damage);
    MainWindow::Instance->Print(name + " has inflicted "+ QString::number(damage) + " points of damage on you");
}
