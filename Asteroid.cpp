#include "Asteroid.h"
#include <vector>
#include <chrono>
#include <thread>


Asteroide::Asteroide(int x, int y) : x(x), y(y), activo(true) {}

void moverAsteroide(Asteroide& asteroide, std::vector<std::vector<char>>& pantalla) {
    // Lógica para mover el asteroide
    asteroide.y += 1;
    if (asteroide.y >= pantalla.size()) {
        asteroide.activo = false;
    }
}

void* ejecutarAsteroide(void* arg) {
    Asteroide* asteroide = (Asteroide*)arg;
    while (asteroide->activo) {
        // Mover el asteroide y pausar el hilo
        asteroide->y += 1;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return nullptr;
}

void dibujarPantallaAsteroides(const std::vector<Asteroide>& asteroides, std::vector<std::vector<char>>& pantalla) {
    for (const Asteroide& asteroide : asteroides) {
        if (asteroide.activo && asteroide.y < pantalla.size() && asteroide.x < pantalla[0].size()) {
            pantalla[asteroide.y][asteroide.x] = 'O';
        }
    }
}

// Definir la lógica de las funciones faltantes para Asteroidec
Asteroidec::Asteroidec(int x, int y) : x(x), y(y), activo(true) {}

void moverAsteroidec(Asteroidec& asteroidec, std::vector<std::vector<char>>& pantalla) {
    // Lógica para mover el asteroide pequeño (Asteroidec)
    asteroidec.y += 1;
    if (asteroidec.y >= pantalla.size()) {
        asteroidec.activo = false;
    }
}

void* ejecutarAsteroidec(void* arg) {
    Asteroidec* asteroidec = (Asteroidec*)arg;
    while (asteroidec->activo) {
        // Mover el asteroide pequeño y pausar el hilo
        asteroidec->y += 1;
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
    return nullptr;
}

void dibujarPantallaAsteroidesc(const std::vector<Asteroidec>& asteroidesc, std::vector<std::vector<char>>& pantalla) {
    for (const Asteroidec& asteroidec : asteroidesc) {
        if (asteroidec.activo && asteroidec.y < pantalla.size() && asteroidec.x < pantalla[0].size()) {
            pantalla[asteroidec.y][asteroidec.x] = 'u';
        }
    }
}
