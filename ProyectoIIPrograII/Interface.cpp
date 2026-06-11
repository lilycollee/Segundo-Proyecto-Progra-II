#include "Interface.h"
#include <sstream>
#include <vector>
#include <iomanip>
#include <limits>
#include <random>
#include <ctime>

Interface::Interface(int width) : boxWidth(width) {}

// ------------------------ Metodos privados ------------------------
void Interface::printTopBar(const std::string& title) const {
    int titleLen  = (int)title.size() + 2;
    int sideLen   = (boxWidth - titleLen) / 2;
    int rightSide = boxWidth - titleLen - sideLen;
    std::cout << "[" << std::string(sideLen, '=') << " " << title << " " << std::string(rightSide, '=') << "]\n";
}

void Interface::printBottom() const {
    std::cout << "[" << std::string(boxWidth, '=') << "]\n";
}


// ejemplo -->  energy[****************....] 80%
std::string Interface::percentageBar(const std::string& label, double value, int width) const {
    int line = static_cast<int>(value / 100.0 * width);     //calcula el numero de caracteres y la cantidad llenos y vacios, redondea y devuelve un en entero
    if (line < 0) {
        line = 0;
    }
    if (line > width) {
        line = width;
    }
    std::string bar = "[";
    bar += std::string(line, '*');                //caracteres para representar el espacio ocupado-todavia disponible
    bar += std::string(width - line, '.');      // caracteres para el espacio libre - usado
    bar += "]";
    std::ostringstream oss;
    oss << std::left << std::setw(10) << label << " " << bar << " " << static_cast<int>(value) << "%";
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

// ------------------------ Impresión ------------------------
void Interface::showBanner() const {
    std::cout << "[================] VOID PROTOCOL [================]\n";
    std::cout << "|Your space base was attacked! Survive through the|\n";
    std::cout << "|rooms until you manage to reach your escape pod. |\n";
    std::cout << "|                                                 |\n";
    std::cout << "|Don't let the corrupt androids or the final boss |\n";
    std::cout << "|catch you!                                       |\n";
    std::cout << "|                                                 |\n";
    std::cout << "|Good luck...!                                    |\n";
    std::cout << "[=================================================]\n\n";
}
void Interface::showBox(const std::string& title, const std::vector<std::string>& lines) const {
    printTopBar(title);
    for (const auto& line : lines) {
        std::string padded = line;
        if ((int)padded.size() < boxWidth) {
            padded += std::string(boxWidth - (int)padded.size(), ' ');
        } else {
            padded = padded.substr(0, boxWidth);
        }
        std::cout << "|" << padded << "|\n";
    }
    printBottom();
}
void Interface::showNote(const std::string& note) const {
    std::cout << "[Note: " << note << "]\n\n";
}
void Interface::showMessage(const std::string& msg) const {
    std::cout << msg << "\n";
}
void Interface::showSeparator() const {
    std::cout << std::string(boxWidth + 2, '-') << "\n";
}

// ------------------------ Lectura ------------------------
int Interface::readOption(int min, int max) const {
    int value = 0;
    while (true) {
        std::cout << "> ";
        if (std::cin >> value && value >= min && value <= max) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid. Try [" << min << "-" << max << "]: ";
    }
}

std::string Interface::readString(const std::string& prompt) const {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin, value);
    return value;
}

void Interface::pause() const {
    std::cout << "Press Enter to continue...\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int Interface::generateInt(int min, int max) const {
    static std::mt19937 gen(std::time(nullptr));
    std::uniform_real_distribution<> dist(min, max);
    return dist(gen);
}
