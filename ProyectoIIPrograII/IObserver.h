#ifndef PROYECTOIIPROGRAII_IOBSERVER_H
#define PROYECTOIIPROGRAII_IOBSERVER_H
#include <iostream>
class IObserver {
public:
    virtual void onEvent(const std::string& event, double value = 0) = 0;
    virtual ~IObserver() = default;
};
#endif //PROYECTOIIPROGRAII_IOBSERVER_H