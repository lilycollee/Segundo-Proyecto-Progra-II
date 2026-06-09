#include "Room.h"
#include <iomanip>
#include <sstream>
Room::Room(std::string name, std::string description, std::vector<Room*> connections, std::vector<Item*> trunk, std::vector<Entity*> entity, int oxygen) {
    this->name = name;
    this->description = description;
    this->connections = connections;
    this->trunk = trunk;
    this->entity = entity;
    this->oxygen = oxygen;
}
std::string Room::getName() {
    return this->name;
}
std::string Room::getDescription() {
    return this->description;
}
int Room::getOxygen() {
    return this->oxygen;
}
std::vector<Room*> Room::getConnections() {
    return this->connections;
}
std::vector<Item*> Room::getTrunk() {
    return this->trunk;
}

std::vector<Entity *> Room::getEntities() {
    return this->entity;
}
void Room::setConnections(std::vector<Room*> conns) {
    connections = conns;
}
void Room::addEntity(Entity* e) {
    entity.push_back(e);
}
void Room::addItem(Item* item) {
    trunk.push_back(item);
}

std::string Room::singleSidedPrinting() {
    std::stringstream s;
    s << "Currente location: [" << name << "]\n";
    s << "Connected rooms:\n";
    if (connections.empty()) {
        s << "  None\n";
    } else {
        for (size_t i = 0; i < connections.size(); i++) {
            s << i << ". [" << connections[i]->getName() << "]\n";
        }
    }
    return s.str();
}

std::string Room::printRooms() {
    std::stringstream s;
    size_t itemCount = trunk.size();
    size_t entityCount = entity.size();
    s << "[" << name << "]\n";
    s << "Description: " << description << "\n";
    s << "Oxygen: " << oxygen << "%\n\n";
    s << "Connections:\n";
    if (connections.empty()) {
        s << "  None\n";
    } else {
        for (size_t i = 0; i < connections.size(); i++) {
            if (i == connections.size() - 1) {
                s << "  └──> [" << connections[i]->getName() << "]\n";
            } else {
                s << "  ├──> [" << connections[i]->getName() << "]\n";
            }
        }
    }
    s << "\nItems:\n";
    if (itemCount == 0) {
        s << "  None\n";
    } else {
        for (size_t i = 0; i < itemCount; i++) {
            if (i == itemCount - 1) {
                s << "  └──> " << trunk[i]->getName() << "\n";
            } else {
                s << "  ├──> " << trunk[i]->getName() << "\n";
            }
        }
    }
    s << "\nEntities:\n";
    if (entityCount == 0) {
        s << "  None\n";
    } else {
        for (size_t i = 0; i < entityCount; i++) {
            if (i == entityCount - 1) {
                s << "  └──> " << entity[i]->getName() << "\n";
            } else {
                s << "  ├──> " << entity[i]->getName() << "\n";
            }
        }
    }
    return s.str();
}
Room::~Room() {}