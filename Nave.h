
#ifndef NAVE_H
#define NAVE_H

#include <vector>
#include <string>
#include "Proyectil.h"

using namespace std;

const vector<string> NAVE_ASCII = {"A", ">", "V", "<"};

struct Nave {
    int x, y;
    int direccion;
    bool running;

    int puntos;
    int vidas;
    vector<Proyectil> proyectiles;

    Nave(int x, int y, int vidasIniciales);

    // Nuevas funciones para movimiento y disparo
    void disparar();
    void moverArriba();
    void moverAbajo();
    void moverIzquierda();
    void moverDerecha();
    void restarVida() { vidas--; }
    int getX() const { return x; }
    int getY() const { return y; }
};

void moverNave(Nave& nave, char input);
void* ejecutarNave(void* arg);
void dibujarPantallaNave(const Nave& nave, vector<vector<char>>& pantalla);

#endif // NAVE_H
