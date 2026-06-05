#ifndef PROYECTOIIPROGRAII_ROOM_H
#define PROYECTOIIPROGRAII_ROOM_H
#include <iostream>
#include <vector>
#include "Entity.h"
#include "Item.h"
class Room {
private:
    std::string name;
    std::string description;
    std::vector<Room*> connections;
    std::vector<Item*> trunk;
    std::vector<Entity*> entity;
    int oxygen;
public:
    // --------------- Base Methods ---------------
    Room(std::string name, std::string description, std::vector<Room*> connections, std::vector<Item*> trunk, std::vector<Entity*> entity, int oxygen);
    std::string getName();
    std::string getDescription();
    int getOxygen();
    std::vector<Room*> getConnections();

    // --------------- Printing Method ---------------
    std::string singleSidedPrinting();
    std::string printRooms();

    // --------------- Destructor ---------------
    ~Room();
};
#endif //PROYECTOIIPROGRAII_ROOM_H