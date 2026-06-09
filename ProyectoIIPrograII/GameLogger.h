#ifndef PROYECTOIIPROGRAII_GAMELOGGER_H
#define PROYECTOIIPROGRAII_GAMELOGGER_H
#include <string>
#include <fstream>
#include "IObserver.h"
class GameLogger : public IObserver {
private:
    std::ofstream logFile;
public:
    GameLogger();
    ~GameLogger();
    void log(const std::string& message);
    void onEvent(const std::string& event, double value = 0) override;
    void writeReport(const std::string& summary);
};
#endif //PROYECTOIIPROGRAII_GAMELOGGER_H