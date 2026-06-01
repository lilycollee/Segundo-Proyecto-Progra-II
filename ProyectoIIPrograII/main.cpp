#include <iostream>
#include "Player.h"
#include "Androide.h"
int main() {
    std::cout << "Hola" << std::endl;

    Player pl;
    Androide andro("An-000");

    std::cout << "PLAYER\n" << pl.showEntity() << std::endl;

    std::cout << "ANDROIDE\n" << andro.showEntity() << std::endl;

}