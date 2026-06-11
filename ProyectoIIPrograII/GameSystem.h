#ifndef PROYECTOIIPROGRAII_GAMESYSTEM_H
#define PROYECTOIIPROGRAII_GAMESYSTEM_H

#include <iostream>
#include <vector>
#include <string>
#include "Player.h"
#include "Room.h"
#include "Android.h"
#include "GameLogger.h"
#include "Alien.h"
#include "Interface.h"
class GameSystem {
private:
    Player* player;
    Room* currentRoom;
    std::vector<Room*> allRooms;
    Interface hud;
    GameLogger logger;
    Interface ui;
    bool gameOver;
    bool playerWon;
    std::string difficulty;

    // ----------- Menús -----------
    void menuMain();
    void menuManual();
    void menuDifficulty();
    void menuItems();
    void menuItemType(const std::string& type);
    void menuGame();
    void menuCombat(Android* android);
    void menuBossFight();

    // ----------- Acciones en el juego -----------
    void actionMove();
    void actionLookAround();
    void actionPickUpItem();
    void actionUseItem();
    void actionFightAndroid();

    // ----------- Revisar estado -----------
    void loadWorld();
    void checkState();
    void endGame();
    void resetGame();

    // ----------- Simulación -----------
    void bossFightSimulator();
    void menuSimulation();
    void runSimulation();

public:
    GameSystem();
    ~GameSystem();
    void start();
};
#endif //PROYECTOIIPROGRAII_GAMESYSTEM_H