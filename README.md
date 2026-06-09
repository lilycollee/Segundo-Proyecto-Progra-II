# VOID PROTOCOL
### EIF204 Programación II — Proyecto Final | Universidad Nacional de Costa Rica

---

```
   (")          (°)         :-----:
   -|-         /| |\        { º º }
   / \          ^ ^         (     )
  Player      Android       ^^^ ^^^
                             Alien
```

---

## Descripción

**VOID PROTOCOL** es una simulación interactiva de consola ambientada en la nave espacial abandonada **USS Erebus**.
El jugador debe sobrevivir atravesando habitaciones, evitando androides corruptos y derrotando al jefe final
para llegar al pod de escape.

El proyecto implementa los requisitos de EIF204: POO, herencia, polimorfismo, patrones de diseño,
manejo de archivos y excepciones, todo en C++ estándar (C++20).

---

## Modos de juego

- **Start simulation** — juego interactivo donde el usuario controla al personaje
- **Auto simulation** — la nave se explora automáticamente con IA, ideal para verificar la simulación
- **Manual game** — configura nombre, dificultad e items antes de jugar

---

## Características

- Exploración de habitaciones conectadas, cargadas desde archivos de texto
- Sistema de inventario con mochila (patrón Composite)
- Combate contra androides de tres niveles de dificultad (Easy / Medium / Hard)
- Combate contra jefe final: el Alien (patrón Singleton)
- Oxígeno y energía como recursos que se agotan durante el juego
- Tres niveles de dificultad que ajustan el daño recibido
- Bitácora de eventos guardada en `log.txt` y mostrada al finalizar
- Reporte final guardado en `report.txt`

---

## Estructura del proyecto

```
ProyectoIIPrograII/
│
├── main.cpp                  # Punto de entrada
│
├── data/                     # Archivos de configuración del mundo
│   ├── rooms.txt
│   ├── connections.txt
│   ├── androids.txt
│   └── items.txt
│
├── Entity / Player / Android / Alien
│   ├── Entity.h / .cpp       # Clase base abstracta
│   ├── Player.h / .cpp       # Jugador con mochila y estadísticas
│   ├── Android.h / .cpp      # Enemigo con niveles de daño
│   └── Alien.h / .cpp        # Jefe final (Singleton)
│
├── Item / Inventario (Composite)
│   ├── Item.h                # Interfaz base
│   ├── Backpack.h / .cpp     # Contenedor principal
│   ├── Weapon / Consumable / Keys
│   ├── OxygenTank / MedicalEquipment
│   └── LaserGun / DeactivationKey / AccessKey
│
├── Observer
│   ├── IObserver.h / IObservable.h
│   ├── GameLogger.h / .cpp   # Escribe log.txt y report.txt
│   └── Interface.h / .cpp    # HUD en consola con barras de estado
│
├── Mundo y sistema
│   ├── Room.h / .cpp         # Habitación con entidades e items
│   ├── WorldLoader.h / .cpp  # Carga el mundo desde archivos .txt
│   └── GameSystem.h / .cpp   # Lógica principal, menús y simulación automática
│
└── CMakeLists.txt
```

---

## Patrones de diseño implementados

| Patrón | Dónde |
|--------|-------|
| **Singleton** | `Alien` — una sola instancia del jefe final |
| **Observer** | `Player` notifica a `GameLogger` e `Interface` cuando cambian energía/oxígeno |
| **Composite** | `Backpack` contiene `Item*`: armas, consumibles, llaves |

---

## Mapa de la nave USS Erebus

```
[Airlock 0]
     |
[Corridor A 1]  ← AN-101 (Easy)
   /     \
[Storage 2]   [Medical 3]
 AN-204(Easy)   MedKit
 O2 + Key
     \
[Corridor B 4]  ← AN-317 (Medium), AccessKey
   /     \
[Engineering 5] [Crew Quarters 6]
 AN-408(Med)     O2 + Key + MedKit
 AdvMedKit
                      |
                 [Bridge 7]  ← AN-512 (Hard), Plasma Rifle X9 
                      |
                 [Corridor C 8]  ← AN-603 (Hard)
                      |
                 [Reactor Core 9]  ← ALIEN BOSS
```

---

## Formato de los archivos de datos

### `data/rooms.txt`
```
# id | nombre | descripción | oxígeno
0 | Airlock | Emergency entry point | 95
```

### `data/connections.txt`
```
# roomId_origen | roomId_destino
0 | 1
```

### `data/androids.txt`
```
# nombre | tipo (Easy/Medium/Hard) | roomId
AN-101 | Easy | 1
```

### `data/items.txt`
```
# tipo | nombre | capacidad | roomId
OxygenTank | Emergency O2 Tank | 35 | 2
MedKit | Basic Med Kit | 30 | 3
LaserGun | Plasma Rifle X9 | 0 | 7
DeactivationKey | Override Key | 0 | 2
```

Tipos de items válidos: `OxygenTank`, `MedKit`, `LaserGun`, `DeactivationKey`, `AccessKey`

---

## Compilación y ejecución

**Requisitos:** CMake 3.x, compilador C++20 (GCC / Clang / MSVC)

```bash
# Desde la raíz del proyecto
cmake -S ProyectoIIPrograII -B build
cmake --build build
./build/ProyectoIIPrograII
```

> Los archivos `data/` deben estar en el directorio de ejecución del binario.
> En CLion, copiarlos dentro de `cmake-build-debug/data/`.

---

## Archivos de salida

| Archivo | Contenido |
|---------|-----------|
| `log.txt` | Bitácora de eventos en tiempo real (movimientos, combates, muertes) |
| `report.txt` | Reporte final con resultado, dificultad, inventario y estadísticas |

Ambos archivos se generan automáticamente al ejecutar el programa. La bitácora también se imprime en consola al finalizar la simulación.

---

## Autora

Yency Amador Centeno & Edith Nicole Bonilla Martínez — Universidad Nacional de Costa Rica  
Curso: EIF204 Programación II, 2026
