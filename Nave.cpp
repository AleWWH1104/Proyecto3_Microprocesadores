
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

// Función para disparar un proyectil
void Nave::disparar() {
    proyectiles.emplace_back(x, y, direccion);
}

// Funciones para mover la nave
void Nave::moverArriba() {
    if (y > 0) y -= 1;
}

void Nave::moverAbajo() {
    if (y < 19) y += 1;
}

void Nave::moverIzquierda() {
    if (x > 0) x -= 1;
}

void Nave::moverDerecha() {
    if (x < 39) x += 1;
}

// Función para capturar la entrada del usuario sin esperar un Enter
void moverNave(Nave& nave, char input) {
    switch (input) {
        case 'w': 
            nave.moverArriba(); 
            break;
        case 's': 
            nave.moverAbajo(); 
            break;
        case 'a': 
            nave.moverIzquierda(); 
            break;
        case 'd': 
            nave.moverDerecha(); 
            break;
        case 'i': 
            nave.moverArriba(); 
            break;
        case 'k': 
            nave.moverAbajo(); 
            break;
        case 'j': 
            nave.moverIzquierda(); 
            break;
        case 'l': 
            nave.moverDerecha(); 
            break;
    }
}

void dispararProyectil(Nave& nave) {
    nave.disparar();
}

void* ejecutarNave(void* arg) {
    Nave* nave = (Nave*)arg;

    while (nave->running) {
        char input = getch();
        moverNave(*nave, input);

        if (input == 'q') {
            nave->running = false;
        }

        if (input == ' ' || input == 'o') {
            dispararProyectil(*nave);
        }

        std::this_thread::sleep_for(std::chrono::microseconds(50000));
    }

    return nullptr;
}

void dibujarPantallaNave(const Nave& nave, vector<vector<char>>& pantalla) {
    pantalla[nave.y][nave.x] = NAVE_ASCII[nave.direccion][0];
}


// Función para manejar la entrada del Jugador 1
void moverNaveJugador1(Nave& nave, char input) {
    switch (input) {
        case 'w': 
            nave.moverArriba(); 
            break;
        case 's': 
            nave.disparar(); 
            break;
        case 'a': 
            nave.moverIzquierda(); 
            break;
        case 'd': 
            nave.moverDerecha(); 
            break;
        default:
            break;
    }
}

// Función para manejar la entrada del Jugador 2
void moverNaveJugador2(Nave& nave, int input) {
    switch (input) {
        case 72:  // Flecha hacia arriba
            nave.moverArriba(); 
            break;
        case 32:  // Barra espaciadora
            nave.disparar(); 
            break;
        case 75:  // Flecha izquierda
            nave.moverIzquierda(); 
            break;
        case 77:  // Flecha derecha
            nave.moverDerecha(); 
            break;
        default:
            break;
    }
}
