#include "Room.h"
#include "Command.h"


Room::Room(QString description, bool isLocked) {
	this->description = description;
    this->isLocked = isLocked;
}

void Room::setExits(Room *north, Room *east, Room *south, Room *west) {
	if (north != NULL)
		exits["north"] = north;
	if (east != NULL)
		exits["east"] = east;
	if (south != NULL)
		exits["south"] = south;
	if (west != NULL)
		exits["west"] = west;
}

QString Room::shortDescription() {
	return description;
}

QString Room::longDescription() {
    return "Room = " + description + ".\n" + displayItem() + exitString() + DisplayEnemies();
}

QString Room::exitString() {
    QString returnString = "\n  -> exits =";
    for (map<QString, Room*>::iterator i = exits.begin(); i != exits.end(); i++)
		// Loop through map
		returnString += "  " + i->first;	// access the "first" element of the pair (direction as a string)
	return returnString;
}

Room* Room::nextRoom(QString direction) {
    map<QString, Room*>::iterator next = exits.find(direction); //returns an iterator for the "pair"
	if (next == exits.end())
		return NULL; // if exits.end() was returned, there's no room in that direction.
	return next->second; // If there is a room, remove the "second" (Room*)
				// part of the "pair" (<string, Room*>) and return it.
}

void Room::addItem(Item *inItem) {
    //cout <<endl;
    //cout << "Just added" + inItem->getLongDescription();
    itemsInRoom.push_back(inItem);
}

QString Room::displayItem() {
    QString tempString = "  -> items = ";
    int sizeItems = (itemsInRoom.size());
    if (itemsInRoom.size() < 1) {
        tempString = "  -> no items";
        }
    else if (itemsInRoom.size() > 0) {
       int x = (0);
        for (int n = sizeItems; n > 0; n--) {
            tempString = tempString + itemsInRoom[x]->GetName() + "  " ;
            x++;
            }
        }
    return tempString;
}

QString Room::DisplayEnemies() {
    QString tempString = "\n  -> enemies = ";
    int sizeItems = (enemiesInRoom.size());
    if (enemiesInRoom.size() < 1) {
        tempString = "\n  -> no enemy";
        }
    else if (enemiesInRoom.size() > 0) {
       int x = (0);
        for (int n = sizeItems; n > 0; n--) {
            tempString = tempString + enemiesInRoom[x]->getShortDescription() + "  " ;
            x++;
            }
        }
    return tempString;
}

int Room::numberOfItems() {
    return itemsInRoom.size();
}

int Room::isItemInRoom(QString inString)
{
    int sizeItems = (itemsInRoom.size());
    if (itemsInRoom.size() < 1) {
        return false;
        }
    else if (itemsInRoom.size() > 0) {
       int x = (0);
        for (int n = sizeItems; n > 0; n--) {
            // compare inString with short description
            int tempFlag = inString.compare( itemsInRoom[x]->GetName());
            if (tempFlag == 0) {
                itemsInRoom.erase(itemsInRoom.begin()+x);
                return x;
            }
            x++;
            }
        }
    return -1;
}

Item* Room::removeItemFromRoom(int location)
{
    Item *item = itemsInRoom[location];
    itemsInRoom.erase(itemsInRoom.begin() + location);
    return item;
}

bool Room::GetIsLocked()
{
    return isLocked;
}


