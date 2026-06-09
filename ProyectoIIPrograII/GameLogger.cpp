#include "GameLogger.h"
#include "GameLogger.h"
#include <iostream>
#include <ctime>

GameLogger::GameLogger() {
    logFile.open("log.txt", std::ios::out | std::ios::trunc);
    if (!logFile.is_open()) {
        std::cerr << "[GameLogger] Warning: could not open log.txt\n";
    } else {
        std::time_t now = std::time(nullptr);
        logFile << "=== VOID PROTOCOL - EVENT LOG ===\n";
        logFile << "Session started: " << std::ctime(&now);
        logFile << "=================================\n\n";
    }
}
GameLogger::~GameLogger() {
    if (logFile.is_open()) {
        logFile << "\n=== END OF LOG ===\n";
        logFile.close();
    }
}
void GameLogger::log(const std::string& message) {
    if (logFile.is_open()) {
        logFile << "[EVENT] " << message << "\n";
        logFile.flush();
    }
}
void GameLogger::onEvent(const std::string& event, double value) {
    if (!logFile.is_open()) {
        return;
    }
    if (event == "ENERGY_CHANGED") {
        logFile << "[STATUS] Player energy changed to " << static_cast<int>(value) << "%\n";
    } else if (event == "OXYGEN_CHANGED") {
        logFile << "[STATUS] Player oxygen changed to " << static_cast<int>(value) << "%\n";
    } else if (event == "PLAYER_DEAD") {
        logFile << "[!!] CRITICAL: Player has died. Simulation ended.\n";
    }
    logFile.flush();
}
void GameLogger::writeReport(const std::string& summary) {
    std::ofstream report("report.txt", std::ios::out | std::ios::trunc);
    if (!report.is_open()) {
        std::cerr << "[GameLogger] Warning: could not write report.txt\n";
        return;
    }
    std::time_t now = std::time(nullptr);
    report << "=== VOID PROTOCOL - FINAL REPORT ===\n";
    report << "Generated: " << std::ctime(&now);
    report << "=====================================\n\n";
    report << summary;
    report << "\n=====================================\n";
    report.close();
}