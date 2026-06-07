#ifndef PROYECTOIIPROGRAII_ACCESSKEY_H
#define PROYECTOIIPROGRAII_ACCESSKEY_H
#include "Item.h"
class AccessKey : public Item {
private:
    std::string name;
public:
    AccessKey(std::string name);
    std::string getName() const override;
    void setName(std::string name);
    std::string description();
    std::string toString(int nivel) override;
};
#endif //PROYECTOIIPROGRAII_ACCESSKEY_H