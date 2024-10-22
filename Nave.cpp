
#include "Nave.h"
#include "Proyectil.h"
#include <iostream>
#include <pthread.h>
#include <chrono>
#include <conio.h>
#include <thread>

using namespace std;

// Constructor para Nave
Nave::Nave(int x, int y, int vidasIniciales)
    : x(x), y(y), direccion(0), running(true), puntos(0), vidas(vidasIniciales) {}

// Función para mover la nave del Jugador 1
void moverNaveJugador1(Nave& nave, char input) {
    switch (input) {
        case 'w':
            switch (nave.direccion) {
                case 0: if (nave.y > 0) nave.y -= 1; break;
                case 1: if (nave.x < 39) nave.x += 1; break;
                case 2: if (nave.y < 19) nave.y += 1; break;
                case 3: if (nave.x > 0) nave.x -= 1; break;
            }
            break;
        case 'a':
            nave.direccion = (nave.direccion + 3) % 4; // Gira 90 grados a la izquierda
            break;
        case 'd':
            nave.direccion = (nave.direccion + 1) % 4; // Gira 90 grados a la derecha
            break;
        case 's':
            nave.proyectiles.emplace_back(nave.x, nave.y, nave.direccion); // Disparar proyectil
            break;
        default:
            break;
    }
}

// Función para mover la nave del Jugador 2
void moverNaveJugador2(Nave& nave, int input) {
    switch (input) {
        case 72: // Flecha hacia arriba
            switch (nave.direccion) {
                case 0: if (nave.y > 0) nave.y -= 1; break;
                case 1: if (nave.x < 39) nave.x += 1; break;
                case 2: if (nave.y < 19) nave.y += 1; break;
                case 3: if (nave.x > 0) nave.x -= 1; break;
            }
            break;
        case 75: // Flecha hacia la izquierda
            nave.direccion = (nave.direccion + 3) % 4; // Gira 90 grados a la izquierda
            break;
        case 77: // Flecha hacia la derecha
            nave.direccion = (nave.direccion + 1) % 4; // Gira 90 grados a la derecha
            break;
        case 32: // Barra espaciadora para disparar
            nave.proyectiles.emplace_back(nave.x, nave.y, nave.direccion); // Disparar proyectil
            break;
        default:
            break;
    }
}

// Función para ejecutar la lógica de la nave en un hilo
void* ejecutarNave(void* arg) {
    Nave* nave = (Nave*)arg;

    while (nave->running) {
        if (_kbhit()) {
            char input = _getch();
            moverNaveJugador1(*nave, input);
        }
        std::this_thread::sleep_for(std::chrono::microseconds(50000));
    }
    return nullptr;
}

// Función para dibujar la nave en la pantalla
void dibujarPantallaNave(const Nave& nave, vector<vector<char>>& pantalla) {
    pantalla[nave.y][nave.x] = NAVE_ASCII[nave.direccion][0];
}
