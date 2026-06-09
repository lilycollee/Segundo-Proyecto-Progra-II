cmake_minimum_required(VERSION 4.1)
project(ProyectoIIPrograII)

set(CMAKE_CXX_STANDARD 20)

add_executable(ProyectoIIPrograII main.cpp
        Entity.cpp
        Entity.h
        Player.cpp
        Player.h
        Android.h
        Android.cpp
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
        Room.cpp
        Room.h
        IObserver.cpp
        IObserver.h
        IObservable.cpp
        IObservable.h
        GameSystem.cpp
        GameSystem.h
        Interface.cpp
        Interface.h
)
