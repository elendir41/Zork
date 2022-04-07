#include <iostream>
#include "ZorkUL.h"
#include "weapon.h"
#include "key.h"
#include "healthpotion.h"

using namespace std;


//int main(int argc, char *argv[]) {
//	ZorkUL temp;
//	temp.play();
//	return 0;
//}

ZorkUL::ZorkUL() {
    if (Instance == nullptr)
    {
        Instance = this;
    }
}

void ZorkUL::createRooms()  {
	Room *a, *b, *c, *d, *e, *f, *g, *h, *i;
	Room *j;

    a = new Room("A");
        a->addItem(new Item("Magic stone", ObjectType::others));
    b = new Room("B");
        Enemy *gob1 = new Gobelin(2, "Gobelin", EnemyType::Gob, 2);
        b->enemiesInRoom.push_back(gob1);
        b->addItem(new Item("Leaf", ObjectType::others));
    c = new Room("C");
        c->addItem(new Item("Map", ObjectType::others));
    d = new Room("D");
    e = new Room("E");
    f = new Room("F", true);
        d->addItem(new HealthPotion("Potion", ObjectType::potion, 2));
    g = new Room("G");
    h = new Room("H");
        h->addItem(new Weapon("Sword", ObjectType::weapon,  2));
    i = new Room("I");
    j = new Room("J");

    b->addItem(new Key("Key", ObjectType::key, f));


//             (N, E, S, W)
    a->setExits(g, b, d, c);
	b->setExits(NULL, NULL, NULL, a);
	c->setExits(NULL, a, NULL, NULL);
	d->setExits(a, e, NULL, i);
	e->setExits(NULL, NULL, NULL, d);
    f->setExits(NULL, j, NULL, g);
    g->setExits(NULL, f, a, h);
    h->setExits(NULL, g, NULL, NULL);
    i->setExits(NULL, d, NULL, NULL);
    j->setExits(NULL, NULL, NULL, f);

    currentRoom = a;

  rooms.push_back(a);
  rooms.push_back(b);  
  rooms.push_back(c);
  rooms.push_back(d);
  rooms.push_back(e);
  rooms.push_back(f);
  rooms.push_back(g);
  rooms.push_back(h);
  rooms.push_back(i);
  rooms.push_back(j);



}

void ZorkUL::play()
{
    window = MainWindow::Instance;
    printWelcome();
    createRooms();
}

void ZorkUL::printWelcome()
{
    window->Print("Welcome in Zork");
    window->Print("You have to finish the wordle in order to win.");
    window->Print("Be careful, there may be enemies in your way !");
}


void ZorkUL::Teleport()
{
    int r = rand() % rooms.size();
    Room *nextRoom = rooms[r];
    while  (nextRoom->GetIsLocked())
    {
        r = rand() % rooms.size();
        nextRoom = rooms[r];
    }
    currentRoom = nextRoom;
}

void ZorkUL::EnemiesAttack()
{
    for (size_t i = 0; i < currentRoom->enemiesInRoom.size(); i++)
    {
        currentRoom->enemiesInRoom[i]->Attack();
    }
}


void ZorkUL::goRoom(Command command) {
	if (!command.hasSecondWord()) {
		cout << "incomplete input"<< endl;
		return;
	}

    QString direction = command.getSecondWord();

	// Try to leave current room.
	Room* nextRoom = currentRoom->nextRoom(direction);

	if (nextRoom == NULL)
		cout << "underdefined input"<< endl;
	else {
		currentRoom = nextRoom;
        //cout << currentRoom->longDescription() << endl;
	}
}

QString ZorkUL::go(QString direction) {
	//Make the direction lowercase
	//transform(direction.begin(), direction.end(), direction.begin(),:: tolower);
    //Move to the next room
    if (currentRoom->enemiesInRoom.size() > 0)
    {
        return "Some enemies prevent from leaving the room";
    }
	Room* nextRoom = currentRoom->nextRoom(direction);
	if (nextRoom == NULL)
		return("direction null");
	else
	{
        if (!nextRoom->GetIsLocked())
        {
            currentRoom = nextRoom;
            return "Moving to room : " + currentRoom->shortDescription();
        }
        else
        {
            return "Door " + nextRoom->shortDescription() +" is locked !";
        }
	}
}

Room* ZorkUL::GetCurrentRoom()
{
    return currentRoom;
}
