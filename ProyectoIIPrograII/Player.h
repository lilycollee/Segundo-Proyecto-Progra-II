#ifndef SEGUNDO_PROYECTO_PROGRA_II_PLAYER_H
#define SEGUNDO_PROYECTO_PROGRA_II_PLAYER_H
#include "Player.h"
class Player : public Entity {
private:
    std::string name;
    int energy;
    double oxygen;
public:
    //-------------- Basics --------------
    Player();
    int getEnergy();
    void setEnergy(int energy);
    double getOxygen();
    void setOxygen(double oxygen);
    std::string getName() const override;
};
#endif //SEGUNDO_PROYECTO_PROGRA_II_PLAYER_H