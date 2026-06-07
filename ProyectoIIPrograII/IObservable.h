#ifndef PROYECTOIIPROGRAII_IOBSERVABLE_H
#define PROYECTOIIPROGRAII_IOBSERVABLE_H
#include "IObserver.h"
class IObservable : public IObserver {
public:
    virtual void addObserver(IObserver* observer) = 0;
    virtual void removeObserver(IObserver* observer) = 0;
    virtual void notify(const std::string& event, double value = 0) = 0;
    virtual ~IObservable() = default;
};
#endif //PROYECTOIIPROGRAII_IOBSERVABLE_H