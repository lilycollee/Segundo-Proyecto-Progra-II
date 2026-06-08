#include "Interface.h"
#include <sstream>
#include <iomanip>

// ejemplo -->  energy[****************....] 80%
std::string Interface::percentageBar(const std::string& label, double value, int width) const {
    int line = static_cast<int>((value / 100.0) * width);     //calcula el numeor de caracteres y la cantidad llenos y vacios, redondea y devuelve un en entero

    if (line < 0) line = 0;
    if (line > width) line = width;

    std::string bar = "[";
    bar += std::string(line, '*');                //caracteres para representar el espacio ocupado-todavia disponible
    bar += std::string(width - line, '.');      // caracteres para el espacio libre - usado
    bar += "]";

    std::ostringstream oss;
    oss << std::left << std::setw(10) << label
        << " " << bar
        << " " << static_cast<int>(value) << "%";
    return oss.str();
}

void Interface::onEvent(const std::string& event, double value) {
    if (event == "ENERGY_CHANGED") {
        std::cout << "[STATUS] " << percentageBar("Energy", value) << "\n";
    } else if (event == "OXYGEN_CHANGED") {
        std::cout << "[STATUS] " << percentageBar("Oxygen", value) << "\n";
    } else if (event == "PLAYER_DEAD") {
        std::cout << "\n[!!] CRITICAL FAILURE: Player has died.\n";
        std::cout << "     The mission ends here.\n\n";
    }
}