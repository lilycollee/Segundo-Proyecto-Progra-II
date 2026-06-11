#ifndef SEGUNDO_PROYECTO_PROGRA_II_PLAYER_H
#define SEGUNDO_PROYECTO_PROGRA_II_PLAYER_H
#include <iostream>
#include <sstream>
#include <memory>
#include "Entity.h"
#include "Backpack.h"
#include "IObservable.h"
#include "OxygenTank.h"
#include "MedicalEquipment.h"

class Player : public Entity, public IObservable {
private:
    std::vector<IObserver*> observers;
    std::string name;
    int energy;
    double oxygen;
    std::unique_ptr<Backpack> myBackPack;
public:
    //-------------- Basics --------------
    Player();
    Player(std::string name);
    ~Player();
    int getEnergy() const;
    void setEnergy(int energy);
    double getOxygen() const;
    void setOxygen(int oxygen);
    Backpack* getBackpack() const;
    std::string showInformation() const;
    std::string getName() const override;
    void setName(std::string name);
    std::string showEntity() const override;

    //-------------- Own --------------
    void refillOxygen(OxygenTank* oxy);
    void useMedicalKit(MedicalEquipment* kit);
    //void useLaserGun(Weapon* weapon);
    void pickUpItem(Item* item);
    std::string showInventory() const;
    void reset();

    //-------------- Observers  --------------
    void addObserver(IObserver* obs) override;
    void removeObserver(IObserver* obs) override;
    void notify(const std::string& event, double value = 0) override;
};
#endif //SEGUNDO_PROYECTO_PROGRA_II_PLAYER_H