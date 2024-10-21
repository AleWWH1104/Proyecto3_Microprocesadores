#include "Asteroid.h"
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <thread> 

using namespace std;  // Añadir aquí

// Constructor para Asteroide
Asteroide::Asteroide(int x, int y) : x(x), y(y), activo(true) {}

void moverAsteroide(Asteroide& asteroide, vector<vector<char>>& pantalla) {
    if (rand() % 2 == 0) {
        if (asteroide.x > 0) {
            asteroide.x -= 1;
        } else {
            asteroide.x = pantalla[0].size() - 1; // Si llega al borde, reaparece
        }
    } else {
        if (asteroide.y < pantalla.size() - 1) {
            asteroide.y += 1;
        } else {
            asteroide.y = 0; // Si llega al borde, reaparece
        }
    }
}

void* ejecutarAsteroide(void* arg) {
    Asteroide* asteroide = (Asteroide*)arg;
    extern vector<vector<char>> pantalla; // Añadido espacio
    
    while (asteroide->activo) {
        moverAsteroide(*asteroide, pantalla);  // Pasar la pantalla
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
;
    }

    return nullptr;
}

void dibujarPantallaAsteroides(const vector<Asteroide>& asteroides, vector<vector<char>>& pantalla) {
    for (const Asteroide& ast : asteroides) { // Cambiado de auto a Asteroide
        if (ast.activo) {
            pantalla[ast.y][ast.x] = ASTEROIDE_ASCII;  // Dibujar asteroide
        }
    }
}
