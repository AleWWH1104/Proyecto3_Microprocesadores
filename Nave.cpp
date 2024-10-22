#include "Nave.h"
#include "Proyectil.h"
#include <iostream>
#include <pthread.h>
#include <chrono>  // Esta parte funcionará en Windows si usas MinGW o Cygwin
#include <conio.h> // Para capturar entrada sin esperar salto de línea
#include <thread> 

using namespace std;

// Constructor para Nave
Nave::Nave(int x, int y, int vidasIniciales, bool isPlayer1) 
    : x(x), y(y), direccion(0), running(true), puntos(0), vidas(vidasIniciales), isPlayer1(isPlayer1) {}

// Función para capturar la entrada del usuario sin esperar un Enter (ya incluida con conio.h)
void moverNave(Nave& nave, char input) {
    if (nave.isPlayer1) {
        // Controles para el jugador 1
        switch (input) {
            case 'w': // Avanzar en la dirección actual
                switch (nave.direccion) {
                    case 0: if (nave.y > 0) nave.y -= 1; break;
                    case 1: if (nave.x < 39) nave.x += 1; break;
                    case 2: if (nave.y < 19) nave.y += 1; break;
                    case 3: if (nave.x > 0) nave.x -= 1; break;
                }
                break;
            case 'a': nave.direccion = (nave.direccion + 3) % 4; break;
            case 'd': nave.direccion = (nave.direccion + 1) % 4; break;
        }
    } else {
        // Controles para el jugador 2
        switch (input) {
            case 72: // Flecha hacia arriba (código ASCII)
                switch (nave.direccion) {
                    case 0: if (nave.y > 0) nave.y -= 1; break;
                    case 1: if (nave.x < 39) nave.x += 1; break;
                    case 2: if (nave.y < 19) nave.y += 1; break;
                    case 3: if (nave.x > 0) nave.x -= 1; break;
                }
                break;
            case 75: nave.direccion = (nave.direccion + 3) % 4; break; // Flecha izquierda
            case 77: nave.direccion = (nave.direccion + 1) % 4; break; // Flecha derecha
        }
    }
}

void dispararProyectil(Nave& nave) {
    nave.proyectiles.emplace_back(nave.x, nave.y, nave.direccion);
}

void* ejecutarNave(void* arg) {
    Nave* nave = (Nave*)arg;

    while (nave->running) {
        char input = getch();  // Captura la tecla ingresada  
        moverNave(*nave, input);

        if (input == 'q') {
            nave->running = false;
        }

        // Diferenciar las teclas de disparo para cada jugador
        if ((nave->isPlayer1 && input == ' ') || (!nave->isPlayer1 && input == 'o')) { // Espacio para disparar o tecla 'o' para el jugador 2
            dispararProyectil(*nave);
        }

        std::this_thread::sleep_for(std::chrono::microseconds(50000));
    }

    return nullptr;
}

void dibujarPantallaNave(const Nave& nave, vector<vector<char>>& pantalla) {
    pantalla[nave.y][nave.x] = NAVE_ASCII[nave.direccion][0];
}
