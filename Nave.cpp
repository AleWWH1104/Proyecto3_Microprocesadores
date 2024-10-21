#include "Nave.h"
#include "Proyectil.h"
#include <iostream>
#include <pthread.h>
#include <chrono>  //esta parte funcionará en Windows si usas MinGW o Cygwin
#include <conio.h>   // Para capturar entrada sin esperar salto de línea
#include <thread> 


using namespace std;  // Añadir aquí

// Constructor para Nave
Nave::Nave(int x, int y, int vidasIniciales) 
    : x(x), y(y), direccion(0), running(true), vidas(vidasIniciales) {}

// Función para capturar la entrada del usuario sin esperar un Enter (ya incluida con conio.h)
void moverNave(Nave& nave, char input) {
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

        if (input == ' ') { // Espacio para disparar
            dispararProyectil(*nave);
        }

        std::this_thread::sleep_for(std::chrono::microseconds(50000));

    }

    return nullptr;
}

void dibujarPantallaNave(const Nave& nave, vector<vector<char>>& pantalla) {
    pantalla[nave.y][nave.x] = NAVE_ASCII[nave.direccion][0];
}