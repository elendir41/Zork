#ifndef ROOM_H_
#define ROOM_H_

#include <map>
#include <QString>
#include <vector>
#include "item.h"
#include "enemy.h"
#include "mainwindow.h"
#include "Character.h"

using namespace std;
using std::vector;

class Room {

    friend class ZorkUL;
    friend class MainWindow;
    friend void Character::Attack(Enemy *enemy, int index);

private:
    QString description;
    map<QString, Room*> exits;
    QString exitString();
    vector<Enemy*> enemiesInRoom;
    bool isLocked;




public:
    int numberOfItems();
    vector <Item*> itemsInRoom;

    Room(QString description, bool isLocked = false);
	void setExits(Room *north, Room *east, Room *south, Room *west);
    QString shortDescription();
    QString longDescription();
    Room* nextRoom(QString direction);
    void addItem(Item *inItem);
    QString displayItem();
    QString DisplayEnemies();
    int isItemInRoom(QString inString);
    bool GetIsLocked();
    inline void SetIsLocked(bool value) {this->isLocked = value;};
    Item* removeItemFromRoom(int location);
    inline map<QString, Room*> GetExits() {return exits;} ;
};

#endif
