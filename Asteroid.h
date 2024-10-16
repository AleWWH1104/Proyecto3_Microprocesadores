// Asteroid.h
#ifndef ASTEROID_H
#define ASTEROID_H

#include <vector>

using namespace std;

const char ASTEROIDE_ASCII = 'O';

struct Asteroide {
    int x, y;           
    bool activo; // Cambiado de atomic<bool> a bool

    Asteroide(int x, int y);
};

void moverAsteroide(Asteroide& asteroide, vector<vector<char>>& pantalla);
void* ejecutarAsteroide(void* arg);
void dibujarPantallaAsteroides(const vector<Asteroide>& asteroides, vector<vector<char>>& pantalla);

#endif 
