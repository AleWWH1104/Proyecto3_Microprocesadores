
#include "Asteroid.h"
#include "Nave.h"
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <thread> 

using namespace std;

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
    extern vector<vector<char>> pantalla; 
    
    while (asteroide->activo) {
        moverAsteroide(*asteroide, pantalla); 
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return nullptr;
}

void dibujarPantallaAsteroides(const vector<Asteroide>& asteroides, vector<vector<char>>& pantalla) {
    for (const auto& asteroide : asteroides) {
        if (asteroide.activo) {
            pantalla[asteroide.y][asteroide.x] = ASTEROIDE_ASCII;
        }
    }
}

// Nueva función para verificar colisiones con ambas naves
bool verificarColisionAsteroide(const Asteroide& asteroide, const Nave& nave1, const Nave& nave2) {
    if (asteroide.activo) {
        if ((asteroide.x == nave1.getX() && asteroide.y == nave1.getY()) ||
            (asteroide.x == nave2.getX() && asteroide.y == nave2.getY())) {
            return true;
        }
    }
    return false;
}
