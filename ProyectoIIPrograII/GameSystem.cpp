#include "GameSystem.h"
#include "WorldLoader.h"
#include "OxygenTank.h"
#include "MedicalEquipment.h"
#include "DeactivationKey.h"
#include "LaserGun.h"
#include "AccessKey.h"
#include <iomanip>
#include <random>
#include <sstream>

GameSystem::GameSystem() {
    this->player = nullptr;
    this->currentRoom = nullptr;
    this->gameOver = false;
    this->playerWon = false;
    this->difficulty = "Undefined";
}
GameSystem::~GameSystem() {
    for (Room* r : allRooms) {
        delete r;
    }
    delete player;
}
void GameSystem::start() {
    ui.showBanner();
    ui.pause();
    menuMain();
}
// ------------------ Menú principal ------------------
void GameSystem::menuMain() {
    int option;
    do {
        ui.showBox("VOID PROTOCOL", {
            "1. Interactive simulation",
            "2. Auto simulation",
            "3. Manual game",
            "4. Exit the game",
            "",
            "Choose option..."
        });
        option = ui.readOption(1, 4);
        switch (option) {
            case 1:
                resetGame();
                loadWorld();
                if (!player) {
                    player = new Player();
                }
                player->addObserver(&hud);
                player->addObserver(&logger);
                logger.log("Simulation started. Difficulty: " + difficulty);
                ui.showMessage("Iniciar simulación en dificultad: " + difficulty);
                menuGame();
                break;
            case 2:
                resetGame();
                menuSimulation();
                break;
            case 3:
                resetGame();
                menuManual();
                break;
            case 4:
                ui.showMessage("Goodbye, astronaut.");
                break;
            default: ;
        }
    } while (option != 4);
}

// ------------------ Menú juego manual ------------------
void GameSystem::menuManual() {
    int option;
    do {
        ui.showBox("MANUAL GAME", {
            "1. Name your character",
            "2. Select the game difficulty",
            "3. Add items to the game",
            "4. Initiate",
            "",
            "Choose option..."
        });
        option = ui.readOption(1, 4);
        switch (option) {
            case 1: {
                std::string name = ui.readString("Enter your character name: ");
                if (name.empty()) {
                    name = "SpaceMan";
                }
                if (!player) {
                    player = new Player(name);
                } else {
                    player->setName(name);
                }
                ui.showMessage("Name set to: " + name);
                ui.pause();
                break;
            }
            case 2: {
                menuDifficulty();
                break;
            }
            case 3: {
                menuItems();
                break;
            }
            case 4: {
                loadWorld();
                if (!player) {
                    player = new Player();
                }
                player->addObserver(&hud);
                player->addObserver(&logger);
                logger.log("Manual game started. Player: " + player->getName() + " | Difficulty: " + difficulty);
                menuGame();
                break;
            }
            default:;
        }
    } while (option != 4);
}

// ------------------ Menú de dificultad ------------------
void GameSystem::menuDifficulty() {
    ui.showNote("According to the chosen level, the monsters' health will increase or decrease!");
    int option;
    while (difficulty == "Undefined") {
        ui.showBox("GAME DIFFICULTY", {
            "1. Easy",
            "2. Medium",
            "3. Difficult",
            "",
            "Choose option..."
        });
        option = ui.readOption(1, 3);
        switch (option) {
            case 1: {
                difficulty = "Easy";
                ui.showMessage("Difficulty: Easy");
                ui.pause();
                break;
            }
            case 2: {
                difficulty = "Medium";
                ui.showMessage("Difficulty: Medium");
                ui.pause();
                break;
            }
            case 3: {
                difficulty = "Difficult";
                ui.showMessage("Difficulty: Difficult");
                ui.pause();
                break;
            }
            default: ;
        }
    }
}

// ------------------ Menú de Items------------------
void GameSystem::menuItems() {
    ui.showNote("The selected items will be added one per room in the game!");
    int option;
    do {
        ui.showBox("ITEMS", {
            "Select the type of item:",
            "",
            "1. Consumable",
            "2. Weapon",
            "3. Keys",
            "4. Return",
            "",
            "Choose option..."
        });
        option = ui.readOption(1, 4);
        switch (option) {
            case 1: {
                menuItemType("Consumable");
                break;
            }
            case 2: {
                menuItemType("Weapon");
                break;
            }
            case 3: {
                menuItemType("Keys");
                break;
            }
            case 4: {
                break;
            }
            default:;
        }
    } while (option != 4);
}

// ------------------ Menú tipo de Items ------------------
void GameSystem::menuItemType(const std::string& type) {
    int option;
    do {
        if (type == "Consumable") {
            ui.showBox("CONSUMABLE", {"1. Oxygen Tank", "2. Medical Kit", "3. Return", "", "Choose option..."});
            option = ui.readOption(1, 3);
            if (option == 1) {
                logger.log("Item queued: OxygenTank");
                ui.showMessage("Oxygen Tank queued.");
                ui.pause();
            }
            if (option == 2) {
                logger.log("Item queued: MedKit");
                ui.showMessage("Medical Kit queued.");
                ui.pause();
            }
        } else if (type == "Weapon") {
            ui.showBox("WEAPON", {"1. Laser Gun", "2. Return", "", "Choose option..."});
            option = ui.readOption(1, 2);
            if (option == 1) {
                logger.log("Item queued: LaserGun");
                ui.showMessage("Laser Gun queued.");
                ui.pause();
            }
            if (option == 2) {
                option = 3;
            }
        } else {
            ui.showBox("KEYS", {"1. Deactivation Key", "2. Access Key", "3. Return", "", "Choose option..."});
            option = ui.readOption(1, 3);
            if (option == 1) {
                logger.log("Item queued: DeactivationKey");
                ui.showMessage("Deactivation Key queued.");
                ui.pause();
            }
            if (option == 2) {
                logger.log("Item queued: AccessKey");
                ui.showMessage("Access Key queued.");
                ui.pause();
            }
        }
    } while (option != 3);
}

// ------------------ Menú de juego ------------------
void GameSystem::menuGame() {
    gameOver  = false;
    playerWon = false;
    difficulty = "Medium";
    while (!gameOver) {
        ui.showBox("STATUS", {
            "Location : " + currentRoom->getName(),
            "Energy   : " + std::to_string(player->getEnergy()) + "%",
            "Oxygen   : " + std::to_string(static_cast<int>(player->getOxygen())) + "%"
        });
        ui.showBox("ACTIONS", {
            "1. Move",
            "2. Look around",
            "3. Pick up item",
            "4. Use item",
            "5. Fight android here",
            "6. Show inventory",
            "0. Abandon mission",
            "",
            "Choose option..."
        });
        int option = ui.readOption(0, 6);
        switch (option) {
            case 1: {
                actionMove();
                break;
            }
            case 2: {
                actionLookAround();
                break;
            }
            case 3: {
                actionPickUpItem();
                break;
            }
            case 4: {
                actionUseItem();
                break;
            }
            case 5: {
                actionFightAndroid();
                break;
            }
            case 6: {
                ui.showMessage(player->showInventory());
                ui.pause();
                break;
            }
            case 0: {
                logger.log("Player abandoned mission.");
                ui.showMessage("Returning to main menu...");
                ui.pause();
                return;
            }
            default:;
        }
        checkState();
    }
    endGame();
}

// ------------------ Acciones de juego ------------------
void GameSystem::actionMove() {
    auto connections = currentRoom->getConnections();
    if (connections.empty()) {
        ui.showMessage("No exits from this room.");
        ui.pause();
        return;
    }
    std::vector<std::string> lines;
    for (int i = 0; i < (int)connections.size(); i++) {
        lines.push_back(std::to_string(i + 1) + ". " + connections[i]->getName());
    }
    int cancelOpt = (int)connections.size() + 1;
    lines.push_back(std::to_string(cancelOpt) + ". Cancel");
    lines.push_back("");
    lines.push_back("Choose option...");
    ui.showBox("MOVE TO", lines);
    int option = ui.readOption(1, cancelOpt);
    if (option == cancelOpt) return;
    Room* destination = connections[option - 1];
    // Puerta: el Bridge requiere la Bridge Access Card
    if (!canEnter(destination)) {
        ui.showMessage("The Bridge is sealed. You need a Bridge Access Card to enter.");
        logger.log("Access to Bridge denied: player has no access card.");
        ui.pause();
        return;
    }
    currentRoom = destination;
    int drop = (difficulty == "Difficult") ? 12 : (difficulty == "Medium") ? 8 : 5;
    int newOxy = static_cast<int>(player->getOxygen()) - drop;
    player->setOxygen(newOxy < 0 ? 0 : newOxy);
    logger.log("Player moved to: " + currentRoom->getName());
    ui.showMessage("You enter: " + currentRoom->getName());
    if (currentRoom->getName() == "Reactor Core") {
        ui.showMessage("A massive shape stirs in the darkness...");
        ui.pause();
        menuBossFight();
        return;
    }
    ui.pause();
}
void GameSystem::actionLookAround() {
    std::ostringstream oss;
    oss << *currentRoom;
    ui.showMessage(oss.str());
    logger.log("Player looked around: " + currentRoom->getName());
    ui.pause();
}
void GameSystem::actionPickUpItem() {
    auto trunk = currentRoom->getTrunk();
    if (trunk.empty()) {
        ui.showMessage("There are no items here.");
        ui.pause();
        return;
    }
    // Mostrar items disponibles
    std::vector<std::string> lines;
    for (int i = 0; i < (int)trunk.size(); i++) {
        lines.push_back(std::to_string(i + 1) + ". " + trunk[i]->getName());
    }
    int cancelOpt = (int)trunk.size() + 1;
    lines.push_back(std::to_string(cancelOpt) + ". Cancel");
    lines.push_back("");
    lines.push_back("Choose option...");
    ui.showBox("PICK UP ITEM", lines);
    int option = ui.readOption(1, cancelOpt);
    if (option == cancelOpt) {
        return;
    }
    int idx = option - 1;
    Item* item = trunk[idx];
    player->pickUpItem(item);       // mochila toma ownership
    currentRoom->removeItem(idx);   // sala suelta el puntero
    ui.showMessage("You picked up: " + item->getName());
    logger.log("Player picked up: " + item->getName());
    ui.pause();
}
void GameSystem::actionUseItem() {
    auto& items = player->getBackpack()->getItems();
    // Filtrar solo items usables (activos)
    std::vector<int> usableIdx;
    for (int i = 0; i < (int)items.size(); i++) {
        if (auto* oxy = dynamic_cast<OxygenTank*>(items[i])) {
            if (oxy->getActive()) {
                usableIdx.push_back(i);
            }
        } else if (auto* kit = dynamic_cast<MedicalEquipment*>(items[i])) {
            if (kit->getActive()) {
                usableIdx.push_back(i);
            }
        }
    }
    if (usableIdx.empty()) {
        ui.showMessage("No usable items in your backpack.");
        ui.pause();
        return;
    }
    // Mostrar solo los usables
    std::vector<std::string> lines;
    for (int i = 0; i < (int)usableIdx.size(); i++) {
        lines.push_back(std::to_string(i + 1) + ". " + items[usableIdx[i]]->getName());
    }
    int cancelOpt = (int)usableIdx.size() + 1;
    lines.push_back(std::to_string(cancelOpt) + ". Cancel");
    lines.push_back("");
    lines.push_back("Choose option...");
    ui.showBox("USE ITEM", lines);
    int option = ui.readOption(1, cancelOpt);
    if (option == cancelOpt) {
        return;
    }
    Item* chosen = items[usableIdx[option - 1]];
    if (auto* oxy = dynamic_cast<OxygenTank*>(chosen)) {
        player->refillOxygen(oxy);
        ui.showMessage("You use " + oxy->getName() + ". Oxygen restored.");
        logger.log("Player used OxygenTank: " + oxy->getName());
    } else if (auto* kit = dynamic_cast<MedicalEquipment*>(chosen)) {
        player->useMedicalKit(kit);
        ui.showMessage("You use " + kit->getName() + ". Energy restored.");
        logger.log("Player used MedKit: " + kit->getName());
    }
    ui.pause();
}
void GameSystem::actionFightAndroid() {
    for (Entity* e : currentRoom->getEntities()) {
           if (Android* a = dynamic_cast<Android*>(e); a && !a->isOff()) {
               menuCombat(a); return;
           }
    }
    ui.showMessage("No active androids found here.");
    ui.pause();
}

// ------------------ Menú de combate de Androide ------------------
void GameSystem::menuCombat(Android* android) {
    if (!android || android->isOff()) {
        ui.showMessage("This android is already deactivated.");
        ui.pause();
        return;
    }
    logger.log("Combat started: " + android->getName());
    while (!android->isOff() && player->getEnergy() > 0) {
        ui.showMessage(android->showEntity());
        ui.showBox("COMBAT", {
            "Enemy : " + android->getName(),
            "",
            "1. Endure attack",
            "2. Use deactivation key",
            "3. Retreat",
            "",
            "Choose option..."
        });
        int option = ui.readOption(1, 3);
        if (option == 1) {
            double damage = 0;
            android->attack(damage);
            if (difficulty == "Medium") {
                damage *= 1.3;
            }
            if (difficulty == "Difficult") {
                damage *= 1.7;
            }
            int newEnergy = player->getEnergy() - static_cast<int>(damage);
            player->setEnergy(newEnergy < 0 ? 0 : newEnergy);
            ui.showMessage(android->getName() + " hits you for " + std::to_string(static_cast<int>(damage)) + " damage!");
            logger.log(android->getName() + " dealt " + std::to_string(static_cast<int>(damage)) + " damage.");
        }
        else if (option == 2) {
            // Buscar llave de desactivación en la mochila
            bool hasKey = false;
            int keyIdx = -1;
            auto& items = player->getBackpack()->getItems();
            for (int i = 0; i < (int)items.size(); i++) {
                if (dynamic_cast<DeactivationKey*>(items[i])) {
                    hasKey = true;
                    keyIdx = i;
                    break;
                }
            }
            if (!hasKey) {
                ui.showMessage("You don't have a deactivation key!");
                logger.log("Player tried to use key but had none.");
            } else {
                android->turnOff();
                // La llave se consume
                delete items[keyIdx];
                // Necesitamos removeItem en Backpack también
                player->getBackpack()->removeItem(keyIdx);
                ui.showMessage(android->getName() + " deactivated!");
                logger.log("Android " + android->getName() + " deactivated with key.");
            }
        } else {
            ui.showMessage("You retreat.");
            logger.log("Player retreated from " + android->getName());
            break;
        }
    }
    ui.pause();
}

// ------------------ Menú de combate del jefe principal ------------------
void GameSystem::menuBossFight() {
    Alien& alien = Alien::getInstance();
    if (alien.isDefeated()) {
        ui.showMessage("The alien is already dead.");
        return;
    }
    logger.log("BOSS FIGHT started.");
    while (!alien.isDefeated() && player->getEnergy() > 0) {
        ui.showMessage(alien.showEntity());
        ui.showBox("BOSS FIGHT", {
            "Alien HP    : " + std::to_string(static_cast<int>(alien.getHealth())),
            "Your energy : " + std::to_string(player->getEnergy()) + "%",
            "",
            "1. Attack with laser gun",
            "2. Escape from the alien",
            "3. Use item (cure oneself)",
            "4. Search for laser gun",
            "",
            "Choose option..."
        });
        int option = ui.readOption(1, 4);
        switch (option) {
            case 1: {
                // Verificar que tiene la laser gun
                bool hasGun = false;
                auto& items = player->getBackpack()->getItems();
                for (auto* it : items) {
                    if (dynamic_cast<LaserGun*>(it)) { hasGun = true; break; }
                }
                if (!hasGun) {
                    ui.showMessage("You need the Laser Gun to fight the alien!");
                    logger.log("Player tried to attack alien without laser gun.");
                    ui.pause();
                    continue;   // vuelve al inicio del while
                }
                double dmg = (difficulty == "Difficult") ? 18.0 : (difficulty == "Medium") ? 25.0 : 35.0;
                alien.lowerHealth(dmg);
                ui.showMessage("You fire! Alien takes " + std::to_string(static_cast<int>(dmg)) + " damage.");
                logger.log("Player dealt " + std::to_string(static_cast<int>(dmg)) + " to alien.");
                if (!alien.isDefeated()) {
                    double alienDmg = alien.attack();
                    if (difficulty == "Medium") {
                        alienDmg *= 1.3;
                    }
                    if (difficulty == "Difficult") {
                        alienDmg *= 1.7;
                    }
                    int newEnergy = player->getEnergy() - static_cast<int>(alienDmg);
                    player->setEnergy(newEnergy < 0 ? 0 : newEnergy);
                    ui.showMessage("The alien strikes back for " + std::to_string(static_cast<int>(alienDmg)) + "!");
                    logger.log("Alien dealt " + std::to_string(static_cast<int>(alienDmg)) + " to player.");
                }
                break;
            }
            case 2: {
                ui.showMessage("You flee from the Reactor Core!");
                logger.log("Player fled boss fight.");
                auto conns = currentRoom->getConnections();
                if (!conns.empty()) {
                    currentRoom = conns[0];
                }
                break;
            }
            case 3 : {
                actionUseItem();
                break;
            }
            case 4: {
                actionPickUpItem();
                break;
            }
        }
    }

    if (alien.isDefeated()) {
        playerWon = true;
        gameOver  = true;
        logger.log("Alien DEFEATED. Player wins!");
        ui.showMessage("The alien collapses. The ship goes silent.");
        ui.pause();
        return;
    }
    if (player->getEnergy()<= 0 || player->getOxygen()<=0) {
        playerWon = false;
        gameOver = true;
        logger.log("Player lost. He is dead");
        ui.showMessage("A minute of silence. The alien has finished you off...");
        ui.pause();
        return;
    }
}

// ------------------ Acciones en el juego ------------------
bool GameSystem::hasAccessKey() {
    for (auto* it : player->getBackpack()->getItems()) {
        if (dynamic_cast<AccessKey*>(it)) {
            return true;
        }
    }
    return false;
}
bool GameSystem::canEnter(Room* room) {
    // El Bridge esta sellado: requiere la Bridge Access Card.
    if (room->getName() == "Bridge") {
        return hasAccessKey();
    }
    return true;
}
void GameSystem::loadWorld() {
    if (!allRooms.empty()) return;
    try {
        currentRoom = WorldLoader::loadWorld(allRooms);
    } catch (const std::exception& e) {
        ui.showMessage(std::string("[ERROR] ") + e.what());
        ui.pause();
    }
}
void GameSystem::checkState() {
    if (player->getEnergy() <= 0 || player->getOxygen() <= 0) {
        gameOver  = true;
        playerWon = false;
        logger.log("Player died.");
    }
    if (Alien::getInstance().isDefeated()) {
        gameOver  = true;
        playerWon = true;
    }
}
void GameSystem::endGame() {
    if (playerWon) {
        ui.showBox("VOID PROTOCOL", {"MISSION COMPLETE", "You escaped the USS Erebus."});
    } else {
        ui.showBox("VOID PROTOCOL", {"MISSION FAILED", "The ship claims another soul."});
    }
    std::ostringstream report;
    report << "Outcome    : " << (playerWon ? "VICTORY" : "DEFEAT") << "\n";
    report << "Difficulty : " << difficulty << "\n\n";
    report << "--- Player ---\n" << *player;
    report << "\n--- Location ---\n" << currentRoom->getName() << "\n";
    report << "\n--- Inventory ---\n" << player->showInventory();
    logger.writeReport(report.str());
    ui.showMessage("Report saved to report.txt");
    ui.showMessage("Event log  saved to log.txt");
    ui.pause();
    // ------------- Mostrar bitácora completa en consola -------------
    ui.showSeparator();
    ui.showMessage("=== EVENT LOG ===\n");
    std::ifstream logIn("log.txt");
    if (logIn.is_open()) {
        std::string line;
        while (std::getline(logIn, line)) {
            ui.showMessage(line);
        }
        logIn.close();
    } else {
        ui.showMessage("[Could not read log.txt]");
    }
    ui.showSeparator();
    ui.pause();
}
void GameSystem::resetGame() {
    for (Room* r : allRooms) {
        delete r;
    }
    allRooms.clear();
    currentRoom = nullptr;

    Alien::getInstance().reset();

    if (!player) {
        player = new Player();
    } else {
        player->reset();
    }
    player->addObserver(&hud);
    player->addObserver(&logger);

    gameOver  = false;
    playerWon = false;
}

// ------------------ Menús de simulación ------------------

void GameSystem::bossFightSimulator() {
    Alien& alien = Alien::getInstance();
    int lowHP = 40;
    bool playerDead = false;
    bool inCombat = true;

    // Verificar que tiene la laser gun
    bool hasGun = false;
    for (auto* it : player->getBackpack()->getItems()) {
        if (dynamic_cast<LaserGun*>(it)) {
            hasGun = true; break;
        }
    }
    if (!hasGun) {
        ui.showMessage("You need the Laser Gun to fight the alien!");
        logger.log("SIM reached the alien without a laser gun. Cannot win.");
        gameOver = true;
        ui.pause();
        return;
    }

    do {
         double dmg = (difficulty == "Difficult") ? 18.0 : (difficulty == "Medium") ? 25.0 : 35.0;
        alien.lowerHealth(dmg);

        ui.showMessage("You fire! Alien takes " + std::to_string(static_cast<int>(dmg)) + " damage.");
        logger.log("Player dealt " + std::to_string(static_cast<int>(dmg)) + " to alien.");

        if (!alien.isDefeated()) {
            double alienDmg = alien.attack();
            if (difficulty == "Medium") {
                alienDmg *= 1.3;
            }
            if (difficulty == "Difficult") {
                alienDmg *= 1.7;
            }

            int newEnergy = player->getEnergy() - static_cast<int>(alienDmg);

            if (newEnergy < 0) {
                player->setEnergy(0);
            } else {
                player->setEnergy(newEnergy);
            }

            ui.showMessage("The alien strikes back for " + std::to_string(static_cast<int>(alienDmg)) + "!");
            logger.log("Alien dealt " + std::to_string(static_cast<int>(alienDmg)) + " to player.");
        }
        player->setOxygen(player->getOxygen()-5);

        //comprueba que el jugador sigue vivo
        if (player->getOxygen() <= 0 || player->getEnergy() <= 0) {
            playerDead = true;
        }
        else {
            //si tiene energia baja, usa kitMedico
            if (player->getEnergy() <= lowHP && !playerDead) {
                auto& listItem = player->getBackpack()->getItems();
                for (auto* it : listItem) {
                    if (auto* kit = dynamic_cast<MedicalEquipment*>(it); kit && kit->getActive()) {
                        player->useMedicalKit(kit);
                        ui.showMessage("You are ready to continue fighting!");
                        logger.log("Player used MedKit: " + kit->getName());
                        ui.pause();
                        break;
                    }
                }
            }
            //si tiene oxigeno bajo, usa tanqueOxygeno
            if (player->getOxygen() <= lowHP && !playerDead) {
                auto& listItems = player->getBackpack()->getItems();
                for (auto* it :listItems) {
                    if (auto* oxy = dynamic_cast<OxygenTank*>(it); oxy && oxy->getActive()) {
                        player->refillOxygen(oxy);
                        ui.showMessage("Your oxygen was restored.");
                        logger.log("Player used OxygenTank: " + oxy->getName());
                        ui.pause();
                        break;
                    }
                }
            }
        }

        //si alien o player mueren el combate termina
        if (alien.isDefeated() || playerDead) {
                inCombat = false;
        }

        ui.pause();
    } while(inCombat);

    if (alien.isDefeated()) {
        playerWon = true;
        gameOver  = true;
        logger.log("Alien DEFEATED. Player wins!");
        ui.showMessage("The alien collapses. The ship goes silent.");
    }
    if (!playerWon) {
        gameOver = true;
        logger.log("Player is DEAD.");
        ui.showMessage("A minute of silence. The alien has finished you off...");
        return;
    }
    ui.pause();
}

void GameSystem::menuSimulation() {
    resetGame();
    ui.showBox("AUTO SIMULATION", {
        "The ship will be explored automatically.",
        "Watch the crew navigate the USS Erebus.",

    });
    int opt = ui.generateInt(1,3);
    if (opt == 1) {
        difficulty = "Easy";
    } else if (opt == 2) {
        difficulty = "Medium";
    } else {
        difficulty = "Difficult";
    }
    loadWorld();
    if (!player) {
        player = new Player("SIM-Unit");
    }
    player->addObserver(&hud);
    player->addObserver(&logger);
    logger.log("AUTO SIMULATION started. Difficulty: " + difficulty);
    ui.showMessage("\n>>> AUTO SIMULATION STARTING <<<\n");
    ui.pause();
    runSimulation();
}

// ------------------ Lógica de simulación ------------------
void GameSystem::runSimulation() {
    std::mt19937 rng(std::time(nullptr)); // Semilla aleatoria
    gameOver  = false;
    playerWon = false;
    int stepLimit = 50;
    int step = 0;
    while (!gameOver && step < stepLimit) {
        step++;
        ui.showSeparator();
        ui.showMessage("[ STEP " + std::to_string(step) + " ] Location: " + currentRoom->getName());
        ui.showMessage("  Energy: " + std::to_string(player->getEnergy()) + "%  Oxygen: " + std::to_string(static_cast<int>(player->getOxygen())) + "%");
        // --- Recoger todos los items del cuarto ---
        while (!currentRoom->getTrunk().empty()) {
            Item* item = currentRoom->getTrunk()[0];
            ui.showMessage("  >> Picks up: " + item->getName());
            logger.log("SIM picked up: " + item->getName());
            player->pickUpItem(item);
            currentRoom->removeItem(0);
        }
        // ------------ Usar consumibles si está bajo ------------
        bool usedSomething = true;
        while (usedSomething) {
            usedSomething = false;
            auto& items = player->getBackpack()->getItems();
            for (int i = 0; i < (int)items.size(); i++) {
                if (auto* oxy = dynamic_cast<OxygenTank*>(items[i])) {
                    if (oxy->getActive() && player->getOxygen() < 75) {
                        player->refillOxygen(oxy);
                        ui.showMessage("  >> Uses oxygen tank. Oxygen: " + std::to_string(static_cast<int>(player->getOxygen())) + "%");
                        logger.log("SIM used OxygenTank.");
                        usedSomething = true;
                        break; // reinicia el for desde el principio
                    }
                } else if (auto* kit = dynamic_cast<MedicalEquipment*>(items[i])) {
                    if (kit->getActive() && player->getEnergy() < 75) {
                        player->useMedicalKit(kit);
                        ui.showMessage("  >> Uses med kit. Energy: " + std::to_string(player->getEnergy()) + "%");
                        logger.log("SIM used MedKit.");
                        usedSomething = true;
                        break;
                    }
                }
            }
        }
        // ------------ Pelear androides activos en el cuarto ------------
        for (Entity* e : currentRoom->getEntities()) {
            if (Android* a = dynamic_cast<Android*>(e); a && !a->isOff()) {
                // Buscar llave de desactivación
                bool hasKey = false;
                int keyIdx = -1;
                auto& inv = player->getBackpack()->getItems();
                for (int i = 0; i < (int)inv.size(); i++) {
                    if (dynamic_cast<DeactivationKey*>(inv[i])) {
                        hasKey = true; keyIdx = i; break;
                    }
                }
                if (hasKey) {
                    // Desactivar con llave
                    ui.showMessage("  >> Uses key on " + a->getName());
                    logger.log("SIM deactivated " + a->getName() + " with key.");
                    a->turnOff();
                    delete inv[keyIdx];
                    player->getBackpack()->removeItem(keyIdx);
                } else {
                    // Aguantar el golpe
                    double damage = 0;
                    a->attack(damage);
                    if (difficulty == "Medium")   damage *= 1.3;
                    if (difficulty == "Difficult") damage *= 1.7;
                    int newE = player->getEnergy() - static_cast<int>(damage);
                    player->setEnergy(newE < 0 ? 0 : newE);
                    ui.showMessage("  >> " + a->getName() + " hits for " + std::to_string(static_cast<int>(damage)) + " dmg.");
                    logger.log("SIM took " + std::to_string(static_cast<int>(damage)) + " damage from " + a->getName());
                }
            }
        }
        checkState();
        if (gameOver) {
            break;
        }

        // ------------ Reactor Core: pelear con alien ------------
        if (currentRoom->getName() == "Reactor Core") {
            ui.showMessage("  >> Entering boss fight!");
            ui.pause();
            bossFightSimulator();
            break;
        }

        // ------------ Decidir hacia dónde moverse ------------
        auto allConns = currentRoom->getConnections();
        // Solo considerar salas a las que el bot puede entrar (el Bridge necesita la tarjeta)
        std::vector<Room*> conns;
        for (Room* r : allConns) {
            if (canEnter(r)) {
                conns.push_back(r);
            }
        }
        if (conns.empty()) {
            ui.showMessage("  >> No reachable exits. Simulation stuck.");
            logger.log("SIM stuck — no reachable exits.");
            break;
        }

        // Si tiene laser gun avanza siempre hacia el reactor, si no, elige aleatoriamente entre las conexiones disponibles
        bool hasGun = false;
        for (auto* it : player->getBackpack()->getItems()) {
            if (dynamic_cast<LaserGun*>(it)) {
                hasGun = true; break;
            }
        }
        Room* next = nullptr;
        if (hasGun) {
            // Avanza hacia la última conexión (más profunda en el mapa)
            next = conns.back();
        } else {
            // Movimiento aleatorio
            std::uniform_int_distribution<int> dist(0, (int)conns.size() - 1);
            next = conns[dist(rng)];
        }
        currentRoom = next;
        int drop = (difficulty == "Difficult") ? 12 : (difficulty == "Medium") ? 8 : 5;
        int newOxy = static_cast<int>(player->getOxygen()) - drop;
        player->setOxygen(newOxy < 0 ? 0 : newOxy);
        ui.showMessage("  >> Moves to: " + currentRoom->getName());
        logger.log("SIM moved to: " + currentRoom->getName());
        checkState();
        ui.pause(); // Pausa breve entre pasos para que no sea tan cargado
    }
    if (step >= stepLimit && !gameOver) {
        logger.log("SIM reached step limit without conclusion.");
        ui.showMessage("\n[ SIMULATION TIMEOUT — no conclusion reached ]\n");
        gameOver = true;
    }
    endGame();
}