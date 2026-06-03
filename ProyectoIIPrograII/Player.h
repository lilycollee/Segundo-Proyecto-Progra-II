#ifndef SEGUNDO_PROYECTO_PROGRA_II_PLAYER_H
#define SEGUNDO_PROYECTO_PROGRA_II_PLAYER_H
#include <iostream>
#include <sstream>
#include "Entity.h"
#include "Backpack.h"
#include "OxygenTank.h"
#include "MedicalEquipment.h"

class Player : public Entity {
private:
    std::string name;
    int energy;
    double oxygen;
    Backpack myBackPack;
public:
    //-------------- Basics --------------
    Player();
    Player(std::string name);
    ~Player();
    int getEnergy() const;
    void setEnergy(int energy);
    double getOxygen() const;
    void setOxygen(int oxygen);
    std::string showInformation() const;

    //-------------- Others  --------------
    std::string getName() const override;
    void setName(std::string name);
    std::string showEntity() const override;

    void refillOxygen(OxygenTank* oxy);
    void useMedicalKit(MedicalEquipment* kit);
    //void useLaserGun(Weapon* weapon);
    void pickUpItem(Item* item);
    void showInventory() const;


};
#endif //SEGUNDO_PROYECTO_PROGRA_II_PLAYER_H

/* Player:
 *   ()
 *  -|-
 *  /\
 * Cohete:
 *    /\
 *  <|°|>
 *   ^^
 * Androide:
 *  (°)
 * /| |\
 *  ^^
 * Alien:
 *  :____:
 * { ° ° }
 * (     )
 * ^^^^^^
 */