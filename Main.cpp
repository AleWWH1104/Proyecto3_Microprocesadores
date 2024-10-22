
#include <iostream>
#include <pthread.h>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "Nave.h"      
#include "Asteroid.h"  
#include <thread>

#include "Colision.h"

using namespace std;

// Tamaño de la pantalla
const int filas = 20;     
const int columnas = 40;  

// Pantalla donde se dibujan la nave y los asteroides
vector<vector<char>> pantalla(filas, vector<char>(columnas, ' '));

vector<Asteroide> asteroides; 

// Función para limpiar la pantalla
void limpiarPantalla() {
    for (auto& fila : pantalla) {
        fill(fila.begin(), fila.end(), ' '); 
    }
}

void borrar() {
#ifdef _WIN32
    system("cls");  
#else
    system("clear");  
#endif
}

void dibujarUI(const Nave& nave) {
    cout << "Vidas: " << nave.vidas << "                 Puntos: " << nave.puntos << endl; 
    cout << string(40, '-') << endl; 
}

void moverProyectiles(vector<Proyectil>& proyectiles) {
    for (auto& proyectil : proyectiles) {  
        if (proyectil.activo) {  
            switch (proyectil.direccion) {  
                case 0: proyectil.y -= 1; break; 
                case 1: proyectil.x += 1; break; 
                case 2: proyectil.y += 1; break; 
                case 3: proyectil.x -= 1; break; 
            }

            if (proyectil.y < 0 || proyectil.y >= filas || proyectil.x < 0 || proyectil.x >= columnas) {
                proyectil.activo = false; 
            }
        }
    }
}

void manejarEntrada(Nave& nave1, Nave& nave2, bool multijugador) {
    if (multijugador) {
        // Jugador 1
        if (cin.get() == 'w') nave1.moverArriba();
        if (cin.get() == 's') nave1.moverAbajo();
        if (cin.get() == 'a') nave1.moverIzquierda();
        if (cin.get() == 'd') nave1.moverDerecha();
        if (cin.get() == ' ') nave1.disparar();

        // Jugador 2
        if (cin.get() == 'i') nave2.moverArriba();
        if (cin.get() == 'k') nave2.moverAbajo();
        if (cin.get() == 'j') nave2.moverIzquierda();
        if (cin.get() == 'l') nave2.moverDerecha();
        if (cin.get() == 'o') nave2.disparar();
    } else {
        // Solo Jugador 1
        if (cin.get() == 'w') nave1.moverArriba();
        if (cin.get() == 's') nave1.moverAbajo();
        if (cin.get() == 'a') nave1.moverIzquierda();
        if (cin.get() == 'd') nave1.moverDerecha();
        if (cin.get() == ' ') nave1.disparar();
    }
}

int main() {
    Nave nave1(1, filas / 2, 3);
    Nave nave2(2, filas / 2, 3); 

    bool multijugador = false;
    char seleccion;
    cout << "¿Deseas jugar en modo multijugador? (s/n): ";
    cin >> seleccion;
    if (seleccion == 's' || seleccion == 'S') {
        multijugador = true;
    }

    while (true) {
        limpiarPantalla();
        manejarEntrada(nave1, nave2, multijugador);

        nave1.dibujar(pantalla);
        if (multijugador) nave2.dibujar(pantalla);

        moverProyectiles(nave1.getProyectiles());
        if (multijugador) moverProyectiles(nave2.getProyectiles());

        detectarColisionesNaveAsteroides(nave1, nave2, asteroides);

        dibujarUI(nave1);
        if (multijugador) dibujarUI(nave2);

        borrar();
    }

    return 0;
}
