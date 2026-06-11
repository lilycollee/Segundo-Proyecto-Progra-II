#ifndef PROYECTOIIPROGRAII_ALIEN_H
#define PROYECTOIIPROGRAII_ALIEN_H

#include <iostream>
#include <sstream>
#include "Entity.h"

//implementa singleton
class Alien : public Entity {
private:
    std::string name;
    double health;
    Alien();
public:

    //-------------- Basics --------------

    virtual ~Alien() ;
    static Alien& getInstance();
    double getHealth() const;
    Alien(const Alien&) = delete;
    Alien& operator=(const Alien&) = delete;
    void reset();

    //-------------- Others --------------
    std::string getName() const override;
    std::string showEntity() const override;

    //-------------- Combat --------------
    double attack();                    //le baja vida al player
    void lowerHealth(double damage);    //el player le baja vida hasta matarlo
    bool isDefeated() const;            // True cuando health llegue a 0
};


#endif //PROYECTOIIPROGRAII_ALIEN_H