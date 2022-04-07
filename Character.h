#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <QString>
#include <vector>
#include "item.h"
#include "enemy.h"
#include "weapon.h"
#include "mainwindow.h"
#include "gobelin.h"

#define MAX_ITEMS 6


using namespace std;
using std::vector;


class Character {
friend void MainWindow::on_InventoryButton_clicked();
friend Gobelin::~Gobelin();

private:
    float nbLives;
    QString description;
    vector < Item* > inventory;
    Weapon* currentWeapon;

public:
     inline static Character *Instance = nullptr;

     float GetLives();
     inline int GetNbItems() {return inventory.size(); };

    Character(QString description);
    ~Character();
    QString shortDescription();
    QString longDescription();

    void addItem(Item *Item);
    void Attack(Enemy* enemy, int index);
    void ChangeWeapon(Weapon *newWeapon);
    void ReceiveDamage(float amount);
    void RemoveItem(Item* item);
    bool IsAlreadyInInventory(Item* item);
    Item *GetItem(int index);
    Weapon* GetCurrentWeapon();




};

#endif /*CHARACTER_H_*/
