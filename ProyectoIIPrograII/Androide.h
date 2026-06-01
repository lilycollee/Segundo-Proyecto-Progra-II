#ifndef SEGUNDO_PROYECTO_PROGRA_II_ANDROIDE_H
#define SEGUNDO_PROYECTO_PROGRA_II_ANDROIDE_H

#include <iostream>
#include <sstream>
#include "Entity.h"


class Androide : public Entity {
private:
    std::string name;
    double damage;
    bool inOff;
public:
    //-------------- Basics --------------
    Androide(std::string name_);
    ~Androide();
    void turnOff();
    double getDamage() const;
    void setDamage(double damage);
    void hurt(double& damage);

    //-------------- Others --------------
    std::string getName() const override;
    std::string showEntity() const override;

};

/* Androide:
 *  (°)
 * /| |\
 *  ^ ^
 */

#endif //SEGUNDO_PROYECTO_PROGRA_II_ANDROIDE_H