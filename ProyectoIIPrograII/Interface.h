#ifndef PROYECTOIIPROGRAII_INTERFACE_H
#define PROYECTOIIPROGRAII_INTERFACE_H
#include <iostream>
#include <vector>
#include <string>
#include "IObserver.h"
class Interface : public IObserver {
private:
    int boxWidth;
    void printTopBar(const std::string& title) const;
    void printBottom() const;
    //construye una barra (con caracteres) para mostrar un porcentaje de uso
    std::string percentageBar(const std::string& label, double value, int width = 20) const;
    void onEvent(const std::string &event, double value) override;

public:
    Interface(int width = 33);

    // ----------- Impresión -----------
    void showBanner() const;
    void showBox(const std::string& title, const std::vector<std::string>& lines) const;
    void showNote(const std::string& note) const;
    void showMessage(const std::string& msg) const;
    void showSeparator() const;

    // ----------- Lectura -----------
    int readOption(int min, int max) const;
    std::string readString(const std::string& prompt) const;
    void pause() const;
    int generateInt(int min, int max) const;

    ~Interface() override = default;
};
#endif //PROYECTOIIPROGRAII_INTERFACE_H