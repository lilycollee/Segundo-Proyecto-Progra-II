#ifndef PROYECTOIIPROGRAII_ALIEN_H
#define PROYECTOIIPROGRAII_ALIEN_H

#include <iostream>
#include <sstream>
#include "Entity.h"

class Alien : public Entity {
private:
    std::string name;
    double health;

public:

    //-------------- Basics --------------
    Alien();
    virtual ~Alien();
    double getHealth() const;

    //-------------- Others --------------
    std::string getName() const override;
    std::string showEntity() const override;

    void attack(); //le baja vida al player
    void lowerHealth(); //el player le baja vida hasta matarlo
};


#endif //PROYECTOIIPROGRAII_ALIEN_H