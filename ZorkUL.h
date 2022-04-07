#ifndef ZORKUL_H_
#define ZORKUL_H_

#include "mainwindow.h"
#include "weapon.h"
#include "Command.h"
#include "Room.h"
#include "item.h"
#include "enemy.h"
#include "gobelin.h"
#include <iostream>
#include <QString>

using namespace std;

class ZorkUL {
private:
    Room *currentRoom;
	vector <Room*> rooms;
    MainWindow *window;

	void createRooms();
	void goRoom(Command command);
    void createItems();
    void displayItems();

public:
    inline static ZorkUL *Instance = nullptr;

	ZorkUL();
	void play();
    void Teleport();
    void EnemiesAttack();
    void printWelcome();

    Room* GetCurrentRoom();
    QString go(QString direction);
};

#endif /*ZORKUL_H_*/
