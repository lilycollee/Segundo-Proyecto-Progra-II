#ifndef SEGUNDO_PROYECTO_PROGRA_II_ANDROIDE_H
#define SEGUNDO_PROYECTO_PROGRA_II_ANDROIDE_H

#include <iostream>
#include <sstream>
#include "Entity.h"

class Android : public Entity {
public:
	enum class Type { Easy, Medium, Hard };

private:
    std::string name;
	Type type;
	double minDamage;
    double maxDamage;
    bool inOff;
	/* damage fuerza de impacto
	Tiene un minimo y un maximo porque dependen de la dificuldad del camino
	pueden atacar más leve o fuerte*/
	void setDamageRangeType();

public:
    //-------------- Basics --------------
	Android(std::string name_, Type type);
    ~Android();
	bool isOff() const;
    void turnOff();

    double getMinDamage() const;
    double getMaxDamage() const;
	Type getType() const;

    void attack(double& damage);

    std::string getName() const override;
    std::string showEntity() const override;

};

/* Android:
 *  (°)
 * /| |\
 *  ^ ^
 */

#endif //SEGUNDO_PROYECTO_PROGRA_II_ANDROIDE_H