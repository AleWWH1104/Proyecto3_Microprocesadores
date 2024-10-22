
#ifndef ASTEROID_H
#define ASTEROID_H

#include <vector>

using namespace std;

const char ASTEROIDE_ASCII = 'O';

struct Asteroide {
    int x, y;
    bool activo;

    Asteroide(int x, int y);
};

void moverAsteroide(Asteroide& asteroide, vector<vector<char>>& pantalla);
void* ejecutarAsteroide(void* arg);
void dibujarPantallaAsteroides(const vector<Asteroide>& asteroides, vector<vector<char>>& pantalla);
bool verificarColisionAsteroide(const Asteroide& asteroide, const Nave& nave1, const Nave& nave2); // Nueva función

const char ASTEROIDEC_ASCII = 'u';

struct Asteroidec {
    int x, y;
    bool activo;

    Asteroidec(int x, int y);
};

void moverAsteroidec(Asteroidec& asteroidec, vector<vector<char>>& pantalla);
void* ejecutarAsteroidec(void* arg);
void dibujarPantallaAsteroidesc(const vector<Asteroidec>& asteroidesc, vector<vector<char>>& pantalla);

#endif
