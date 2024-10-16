// Nave.h
#ifndef NAVE_H
#define NAVE_H

#include <vector>
#include <string>

using namespace std; 

const vector<string> NAVE_ASCII = {"A", ">", "V", "<"}; 

struct Nave {
    int x, y;           
    int direccion;     
    bool running;  // Cambiado de atomic<bool> a bool

    Nave(int x, int y);
};

int getch();
void moverNave(Nave& nave, char input);
void* ejecutarNave(void* arg);
void dibujarPantallaNave(const Nave& nave, vector<vector<char>>& pantalla);

#endif // NAVE_H
