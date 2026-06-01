#ifndef SEGUNDO_PROYECTO_PROGRA_II_ENTITY_H
#define SEGUNDO_PROYECTO_PROGRA_II_ENTITY_H
#include <iostream>
class Entity {
public:
    virtual std::string getName() const = 0;
    virtual ~Entity() = default;
    virtual std::string showEntity() const = 0;

};
#endif //SEGUNDO_PROYECTO_PROGRA_II_ENTITY_H