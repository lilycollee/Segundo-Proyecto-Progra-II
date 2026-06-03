#include <iostream>
#include "Alien.h"
#include "Android.h"
#include "Player.h"
int main() {
    Player pl;
    Android andro("An-000",Android::Type::Easy);
    //Alien ali;

    std::cout << "PLAYER\n" << pl.showEntity() << std::endl;

    std::cout << "ANDROID\n" << andro.showEntity() << std::endl;

    //std::cout << "ALIEN\n" << ali.showEntity() << std::endl;
}