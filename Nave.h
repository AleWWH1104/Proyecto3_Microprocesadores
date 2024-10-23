// Nave.h
#ifndef NAVE_H
#define NAVE_H

#include <vector>
#include <string>
#include "Proyectil.h" 

using namespace std; 

// Constante que almacena la representación ASCII de la nave en diferentes direcciones
const vector<string> NAVE_ASCII = {"A", ">", "V", "<"}; 

// Estructura que representa una nave en el juego
struct Nave {
    int x;                // Posición X de la nave
    int y;                // Posición Y de la nave
    int direccion;        // Dirección en la que está apuntando la nave
    bool running;         // Indica si la nave está en ejecución
    int puntos;           // Puntos del jugador
    int vidas;            // Vidas del jugador
    vector<Proyectil> proyectiles; // Lista de proyectiles disparados por la nave
    bool isPlayer1;       // Indica si la nave pertenece al jugador 1

    // Constructor para inicializar una nave
    Nave(int x, int y, int vidasIniciales, bool isPlayer1);
};

// Funciones para manejar la nave
void moverNave(Nave& nave, char input);                     // Mueve la nave según la entrada
void* ejecutarNave(void* arg);                             // Hilo de ejecución para la nave
void dibujarPantallaNave(const Nave& nave, vector<vector<char>>& pantalla); // Dibuja la nave en la pantalla

#endif // NAVE_H
