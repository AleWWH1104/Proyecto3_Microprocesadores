#include "Nave.h"
#include "Proyectil.h"
#include <iostream>
#include <pthread.h>
#include <chrono>
#include <conio.h>
#include <thread>

using namespace std;

// Declarar filas y columnas como variables externas
extern const int filas;
extern const int columnas;

// Constructor para Nave
Nave::Nave(int x, int y, int vidasIniciales) 
    : x(x), y(y), direccion(0), running(true), puntos(0), vidas(vidasIniciales) {}

// Función para mover la nave
void moverNave(Nave& nave, char input, bool esJugador1) {
    if (esJugador1) {
        switch (input) {
            case 'w': // Avanzar en la dirección actual
                switch (nave.direccion) {
                    case 0: if (nave.y > 0) nave.y -= 1; break;  // Arriba
                    case 1: if (nave.x < columnas - 1) nave.x += 1; break; // Derecha
                    case 2: if (nave.y < filas - 1) nave.y += 1; break; // Abajo
                    case 3: if (nave.x > 0) nave.x -= 1; break;  // Izquierda
                }
                break;
            case 'a': nave.direccion = (nave.direccion + 3) % 4; break;  // Girar a la izquierda
            case 'd': nave.direccion = (nave.direccion + 1) % 4; break;  // Girar a la derecha
        }
    } else {
        switch (input) {
            case 72: // Flecha hacia arriba
                switch (nave.direccion) {
                    case 0: if (nave.y > 0) nave.y -= 1; break;  // Arriba
                    case 1: if (nave.x < columnas - 1) nave.x += 1; break; // Derecha
                    case 2: if (nave.y < filas - 1) nave.y += 1; break; // Abajo
                    case 3: if (nave.x > 0) nave.x -= 1; break;  // Izquierda
                }
                break;
            case 75: nave.direccion = (nave.direccion + 3) % 4; break;  // Flecha izquierda
            case 77: nave.direccion = (nave.direccion + 1) % 4; break;  // Flecha derecha
        }
    }
}

// Función para disparar un proyectil
void dispararProyectil(Nave& nave) {
    nave.proyectiles.emplace_back(nave.x, nave.y, nave.direccion);
}

// Hilo que ejecuta el movimiento y disparo de la nave
void* ejecutarNave(void* arg) {
    Nave* nave = (Nave*)arg;
    bool esJugador1 = (nave->x < 10);  // Si la nave está a la izquierda, es Jugador 1

    while (nave->running) {
        char input = getch();  // Captura la tecla ingresada
        moverNave(*nave, input, esJugador1);

        if (esJugador1 && input == 'q') {
            nave->running = false;
        } else if (!esJugador1 && input == 27) {  // Jugador 2 sale con ESC
            nave->running = false;
        }

        // Disparo de proyectil (Espacio o Enter)
        if (input == ' ' || input == 13) {
            dispararProyectil(*nave);
        }

        std::this_thread::sleep_for(std::chrono::microseconds(50000));
    }

    return nullptr;
}

// Función para dibujar la nave en la pantalla
void dibujarPantallaNave(const Nave& nave, vector<vector<char>>& pantalla) {
    pantalla[nave.y][nave.x] = NAVE_ASCII[nave.direccion][0];
}

// Función para mover proyectiles
void moverProyectiles(vector<Proyectil>& proyectiles) {
    for (auto& proyectil : proyectiles) {
        if (proyectil.activo) {
            switch (proyectil.direccion) {
                case 0: proyectil.y -= 1; break; // Arriba
                case 1: proyectil.x += 1; break; // Derecha
                case 2: proyectil.y += 1; break; // Abajo
                case 3: proyectil.x -= 1; break; // Izquierda
            }

            // Si el proyectil sale de la pantalla, se desactiva
            if (proyectil.y < 0 || proyectil.y >= filas || proyectil.x < 0 || proyectil.x >= columnas) {
                proyectil.activo = false;
            }
        }
    }
}

// Función para dibujar los proyectiles en la pantalla
void dibujarProyectiles(const vector<Proyectil>& proyectiles, vector<vector<char>>& pantalla) {
    for (const auto& proyectil : proyectiles) {
        if (proyectil.activo) {
            pantalla[proyectil.y][proyectil.x] = '*';  // Representación del proyectil
        }
    }
}
