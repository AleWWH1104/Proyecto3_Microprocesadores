
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
        std::this_thread::sleep_for(std::chrono::microseconds(350000));
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

// Asteroide pequeño (Asteroidec)
Asteroidec::Asteroidec(int x, int y) : x(x), y(y), activo(true) {}

void moverAsteroidec(Asteroidec& asteroidec, vector<vector<char>>& pantalla) {
    if (rand() % 2 == 0) {
        if (asteroidec.x > 0) {
            asteroidec.x -= 1;
        } else {
            asteroidec.x = pantalla[0].size() - 1; // Si llega al borde, reaparece
        }
    } else {
        if (asteroidec.y < pantalla.size() - 1) {
            asteroidec.y += 1;
        } else {
            asteroidec.y = 0; // Si llega al borde, reaparece
        }
    }
}

void* ejecutarAsteroidec(void* arg) {
    Asteroidec* asteroidec = (Asteroidec*)arg;
    extern vector<vector<char>> pantalla; // Añadido espacio
    
    while (asteroidec->activo) {
        moverAsteroidec(*asteroidec, pantalla);  // Pasar la pantalla
        std::this_thread::sleep_for(std::chrono::microseconds(350000));
    }

    return nullptr;
}

void dibujarPantallaAsteroidesc(const vector<Asteroidec>& asteroidesc, vector<vector<char>>& pantalla) {
    for (const Asteroidec& astc : asteroidesc) { // Cambiado de auto a Asteroide
        if (astc.activo) {
            pantalla[astc.y][astc.x] = ASTEROIDEC_ASCII;  // Dibujar asteroide
        }
    }
}
    