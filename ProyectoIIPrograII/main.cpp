#include <iostream>
#include "Alien.h"
#include "Androide.h"
#include "Player.h"
int main() {
    std::cout << "Hola" << std::endl;

    Player pl;
    Androide andro("An-000");
    Alien ali;

    std::cout << "PLAYER\n" << pl.showEntity() << std::endl;

    std::cout << "ANDROIDE\n" << andro.showEntity() << std::endl;

    std::cout << "ALIEN\n" << ali.showEntity() << std::endl;
}