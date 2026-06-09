#ifndef PROYECTOIIPROGRAII_WORLDLOADER_H
#define PROYECTOIIPROGRAII_WORLDLOADER_H
#include <vector>
#include <string>
#include "Room.h"
#include "Android.h"
#include "Item.h"
class WorldLoader {
private:
    static std::vector<std::string> splitLine(const std::string& line);
    static Android::Type parseAndroidType(const std::string& s);
public:
    static Room* loadWorld(std::vector<Room*>& allRooms);
};
#endif //PROYECTOIIPROGRAII_WORLDLOADER_H