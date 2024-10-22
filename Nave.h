#ifndef NAVE_H
#define NAVE_H

#include <vector>
#include "Proyectil.h"  // Añadir esta línea para declarar el tipo Proyectil
using namespace std;

const vector<vector<char>> NAVE_ASCII = {{'^'}, {'>'}, {'v'}, {'<'}};

struct Nave {
    int x, y;
    int direccion;  // 0: Arriba, 1: Derecha, 2: Abajo, 3: Izquierda
    bool running;
    int puntos;
    int vidas;
    vector<Proyectil> proyectiles;  // Proyectiles disparados

    Nave(int x, int y, int vidasIniciales);
};

void moverNave(Nave& nave, char input, bool esJugador1);
void dispararProyectil(Nave& nave);
void* ejecutarNave(void* arg);
void dibujarPantallaNave(const Nave& nave, vector<vector<char>>& pantalla);
void moverProyectiles(vector<Proyectil>& proyectiles);
void dibujarProyectiles(const vector<Proyectil>& proyectiles, vector<vector<char>>& pantalla);

#endif
