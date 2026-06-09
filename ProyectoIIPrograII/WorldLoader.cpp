#include "WorldLoader.h"
#include "Android.h"
#include "OxygenTank.h"
#include "MedicalEquipment.h"
#include "LaserGun.h"
#include "DeactivationKey.h"
#include "AccessKey.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
std::vector<std::string> WorldLoader::splitLine(const std::string& line) {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, '|')) {
        size_t start = token.find_first_not_of(" \t\r");
        size_t end   = token.find_last_not_of(" \t\r");
        if (start != std::string::npos) {
            tokens.push_back(token.substr(start, end - start + 1));
        } else {
            tokens.push_back("");
        }
    }
    return tokens;
}
Android::Type WorldLoader::parseAndroidType(const std::string& s) {
    if (s == "Easy")   return Android::Type::Easy;
    if (s == "Medium") return Android::Type::Medium;
    if (s == "Hard")   return Android::Type::Hard;
    throw std::invalid_argument("Unknown android type: " + s);
}
Room* WorldLoader::loadWorld(std::vector<Room*>& allRooms) {
    // Habitaciones/Rooms
    {
        std::ifstream file("data/rooms.txt");
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open data/rooms.txt");
        }
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') {
                continue;
            }
            auto t = splitLine(line);
            if (t.size() < 4) {
                continue;
            }
            // t[0]=id  t[1]=name  t[2]=description  t[3]=oxygen
            int oxygen = std::stoi(t[3]);
            allRooms.push_back(new Room(t[1], t[2], {}, {}, {}, oxygen));
        }
    }
    //Conecciones de las habitaciones/Rooms
    {
        std::ifstream file("data/connections.txt");
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open data/connections.txt");
        }
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') {
                continue;
            }
            auto t = splitLine(line);
            if (t.size() < 2) {
                continue;
            }
            int from = std::stoi(t[0]);
            int to   = std::stoi(t[1]);
            if (from < (int)allRooms.size() && to < (int)allRooms.size()) {
                std::vector<Room*> conns = allRooms[from]->getConnections();
                conns.push_back(allRooms[to]);
                allRooms[from]->setConnections(conns);
            }
        }
    }
    //Androides
    {
        std::ifstream file("data/androids.txt");
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open data/androids.txt");
        }
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') {
                continue;
            }
            auto t = splitLine(line);
            if (t.size() < 3) {
                continue;
            }
            // t[0]=name  t[1]=type  t[2]=roomId
            Android::Type type = parseAndroidType(t[1]);
            int roomId = std::stoi(t[2]);
            if (roomId < (int)allRooms.size()) {
                allRooms[roomId]->addEntity(new Android(t[0], type));
            }
        }
    }
    //Items
    {
        std::ifstream file("data/items.txt");
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open data/items.txt");
        }
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') {
                continue;
            }
            auto t = splitLine(line);
            if (t.size() < 4) {
                continue;
            }
            // t[0]=type  t[1]=name  t[2]=capacity  t[3]=roomId
            std::string type = t[0];
            std::string name = t[1];
            double capacity  = std::stod(t[2]);
            int roomId       = std::stoi(t[3]);

            if (roomId >= (int)allRooms.size()) {
                continue;
            }
            Item* item = nullptr;
            if (type == "OxygenTank") {
                item = new OxygenTank(name, capacity);
            }
            else if (type == "MedKit") {
                item = new MedicalEquipment(name, capacity);
            }
            else if (type == "LaserGun") {
                item = new LaserGun(name);
            }
            else if (type == "DeactivationKey") {
                item = new DeactivationKey(name);
            }
            else if (type == "AccessKey") {
                item = new AccessKey(name);
            }
            else {
                std::cerr << "[WorldLoader] Unknown item type: " << type << "\n";
                continue;
            }
            allRooms[roomId]->addItem(item);
        }
    }
    if (allRooms.empty()) {
        throw std::runtime_error("No rooms were loaded from data/rooms.txt");
    }
    return allRooms[0]; // room 0 is always the starting room
}