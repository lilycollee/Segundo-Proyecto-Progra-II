cmake_minimum_required(VERSION 4.1)
project(ProyectoIIPrograII)

set(CMAKE_CXX_STANDARD 20)

add_executable(ProyectoIIPrograII main.cpp
        Entity.cpp
        Entity.h
        Player.cpp
        Player.h
        Androide.h
        Androide.cpp
        Consumable.h
        Consumable.cpp
        Backpack.cpp
        Backpack.h
        DeactivationKey.cpp
        DeactivationKey.h
        Item.cpp
        Item.h
        LaserGun.cpp
        LaserGun.h
        MedicalEquipment.cpp
        MedicalEquipment.h
        OxygenTank.cpp
        OxygenTank.h
        Weapon.cpp
        Weapon.h
        Alien.cpp
        Alien.h
        Keys.cpp
        Keys.h
        AccessKey.cpp
        AccessKey.h
)
