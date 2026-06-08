#ifndef PROYECTOIIPROGRAII_INTERFACE_H
#define PROYECTOIIPROGRAII_INTERFACE_H

#include <iostream>
#include <string>
#include "IObserver.h"

class Interface : public IObserver {

private:
    //construye una barra (con caracteres) para mostrar un porcentaje de uso
    std::string percentageBar(const std::string& label, double value, int width = 20) const;

public:
    Interface() = default;
    void onEvent(const std::string& event, double value = 0) override;

};

#endif //PROYECTOIIPROGRAII_INTERFACE_H