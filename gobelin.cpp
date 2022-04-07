#include "gobelin.h"
#include "mainwindow.h"
#include "enemy.h"
#include "Character.h"
#include "healthpotion.h"

Gobelin::Gobelin(float HP, QString name, EnemyType type, float damage)
    : Enemy(name, damage)
{
    this->nbLives = HP;
    this->type = type;
}

Gobelin::~Gobelin()
{
    vector<Item*> &items = Character::Instance->inventory;
    for (size_t i = 0; i < items.size(); i++)
    {
        if (items[i]->GetType() == ObjectType::potion)
        {
            HealthPotion *p =  (HealthPotion *) items[i];
            items.push_back(p);
            MainWindow::Instance->Print("The goblin dropped a magic stone that duplicated one of your potions");
            break;
        }
    }

    MainWindow::Instance->Print(name + " is dead !");
}

void Gobelin::PrintInfo()
{
    QString message = name + " has " + QString::number( nbLives) + " healthpoints";
    MainWindow::Instance->Print(message);
}

QString Gobelin::getShortDescription()
{
    return name;
}
