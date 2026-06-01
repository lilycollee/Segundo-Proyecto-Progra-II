#ifndef PROYECTOIIPROGRAII_ITEM_H
#define PROYECTOIIPROGRAII_ITEM_H
#include <iostream>
class Item {
public:
    virtual std::string getName() const = 0;
    virtual std::string toString(int nivel = 0) = 0;
    virtual ~Item() {}
};
#endif //PROYECTOIIPROGRAII_ITEM_H