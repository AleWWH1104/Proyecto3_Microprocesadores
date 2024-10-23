#include "Asteroid.h"  // Incluir la definición de la clase Asteroide
#include <iostream>    // Incluir la librería para operaciones de entrada/salida
#include <chrono>      // Incluir para manejar el tiempo
#include <cstdlib>     // Incluir para funciones de generación de números aleatorios
#include <ctime>       // Incluir para manejo del tiempo
#include <thread>      // Incluir para manejar hilos

using namespace std;  // Usar el espacio de nombres estándar para simplificar el código

// Constructor para la clase Asteroide
Asteroide::Asteroide(int x, int y) : x(x), y(y), activo(true) {} // Inicializar las coordenadas y estado del asteroide

// Función que mueve un asteroide en la pantalla
void moverAsteroide(Asteroide& asteroide, vector<vector<char>>& pantalla) {
    // Determinar aleatoriamente la dirección en la que se moverá el asteroide
    if (rand() % 2 == 0) {
        // Mover hacia la izquierda
        if (asteroide.x > 0) {
            asteroide.x -= 1; // Mover una posición a la izquierda
        } else {
            asteroide.x = pantalla[0].size() - 1; // Si llega al borde, reaparece en el lado derecho
        }
    } else {
        // Mover hacia abajo
        if (asteroide.y < pantalla.size() - 1) {
            asteroide.y += 1; // Mover una posición hacia abajo
        } else {
            asteroide.y = 0; // Si llega al borde, reaparece en la parte superior
        }
    }
}

// Función que ejecuta el movimiento de un asteroide en un hilo separado
void* ejecutarAsteroide(void* arg) {
    Asteroide* asteroide = (Asteroide*)arg; // Convertir el argumento a un puntero de tipo Asteroide
    extern vector<vector<char>> pantalla; // Declarar pantalla como externa para usarla aquí
    
    // Bucle para mover el asteroide mientras esté activo
    while (asteroide->activo) {
        moverAsteroide(*asteroide, pantalla); // Llamar a la función que mueve el asteroide
        std::this_thread::sleep_for(std::chrono::microseconds(350000)); // Esperar un tiempo antes de la siguiente actualización
    }

    return nullptr; // Retornar nullptr al finalizar
}

// Función para dibujar los asteroides en la pantalla
void dibujarPantallaAsteroides(const vector<Asteroide>& asteroides, vector<vector<char>>& pantalla) {
    for (const Asteroide& ast : asteroides) { // Iterar sobre cada asteroide en el vector
        if (ast.activo) {
            pantalla[ast.y][ast.x] = ASTEROIDE_ASCII; // Dibujar el asteroide en la pantalla usando un carácter ASCII
        }
    }
}

// Clase Asteroidec (posiblemente una versión más pequeña del asteroide)
Asteroidec::Asteroidec(int x, int y) : x(x), y(y), activo(true) {} // Constructor para Asteroidec

// Función que mueve un asteroide pequeño (Asteroidec) en la pantalla
void moverAsteroidec(Asteroidec& asteroidec, vector<vector<char>>& pantalla) {
    // Determinar aleatoriamente la dirección en la que se moverá el asteroide pequeño
    if (rand() % 2 == 0) {
        // Mover hacia la izquierda
        if (asteroidec.x > 0) {
            asteroidec.x -= 1; // Mover una posición a la izquierda
        } else {
            asteroidec.x = pantalla[0].size() - 1; // Si llega al borde, reaparece en el lado derecho
        }
    } else {
        // Mover hacia abajo
        if (asteroidec.y < pantalla.size() - 1) {
            asteroidec.y += 1; // Mover una posición hacia abajo
        } else {
            asteroidec.y = 0; // Si llega al borde, reaparece en la parte superior
        }
    }
}

// Función que ejecuta el movimiento de un asteroide pequeño en un hilo separado
void* ejecutarAsteroidec(void* arg) {
    Asteroidec* asteroidec = (Asteroidec*)arg; // Convertir el argumento a un puntero de tipo Asteroidec
    extern vector<vector<char>> pantalla; // Declarar pantalla como externa para usarla aquí
    
    // Bucle para mover el asteroide pequeño mientras esté activo
    while (asteroidec->activo) {
        moverAsteroidec(*asteroidec, pantalla); // Llamar a la función que mueve el asteroide pequeño
        std::this_thread::sleep_for(std::chrono::microseconds(350000)); // Esperar un tiempo antes de la siguiente actualización
    }

    return nullptr; // Retornar nullptr al finalizar
}

// Función para dibujar los asteroides pequeños en la pantalla
void dibujarPantallaAsteroidesc(const vector<Asteroidec>& asteroidesc, vector<vector<char>>& pantalla) {
    for (const Asteroidec& astc : asteroidesc) { // Iterar sobre cada asteroide pequeño en el vector
        if (astc.activo) {
            pantalla[astc.y][astc.x] = ASTEROIDEC_ASCII; // Dibujar el asteroide pequeño en la pantalla usando un carácter ASCII
        }
    }
}
