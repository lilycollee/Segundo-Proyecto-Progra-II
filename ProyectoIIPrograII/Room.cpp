#include "Room.h"
#include <sstream>
Room::Room(std::string name, std::string description, std::vector<Room*> connections, std::vector<Item*> trunk, std::vector<Entity*> entity, int energy) {
    this->name = name;
    this->description = description;
    this->connections = connections;
    this->trunk = trunk;
    this->entity = entity;
    this->energy = energy;
}
std::string Room::getName() {
    return this->name;
}
std::string Room::getDescription() {
    return this->description;
}
std::vector<Room*> Room::getConnections() {
    return this->connections;
}
std::string Room::printRoom() {
    std::stringstream s;
    s << " ";
    for (int i = 0; i < name.length() + 2; i++)
        s << "-";
    s << "\n";
    s << "| " << name << " |" << "\n";
    s << " ";
    for (int i = 0; i < name.length() + 2; i++)
        s << "-";
    s << "\n";
    return s.str();
}
std::string Room::printRooms() {
    std::stringstream s;
    if (connections.empty()) {
        return "It does not have any connection to another added room. \n";
    }
    int quantity = this->connections.size();
    if (quantity == 1) {
        s << printRoom() << "";
    }
}