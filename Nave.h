// Nave.h
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
    bool running;  // Cambiado de atomic<bool> a bool

    int puntos;
    int vidas;// vidas, pata logica de colision
    vector<Proyectil> proyectiles; // Almacenar los proyectiles
    bool isPlayer1; // Nueva bandera para indicar si es el jugador 1 o 2
    Nave(int x, int y, int vidasIniciales, bool isPlayer1);
};

void moverNave(Nave& nave, char input);
void* ejecutarNave(void* arg);
void dibujarPantallaNave(const Nave& nave, vector<vector<char>>& pantalla);

#endif // NAVE_H
