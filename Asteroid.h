// Asteroid.h
#ifndef ASTEROID_H   // Verificar si ASTEROID_H no ha sido definido
#define ASTEROID_H   // Definir ASTEROID_H para evitar inclusiones múltiples

#include <vector>     // Incluir la librería de vectores de C++

using namespace std;  // Usar el espacio de nombres estándar

// Definir un carácter ASCII que representa un asteroide
const char ASTEROIDE_ASCII = 'O';

// Estructura que representa un asteroide
struct Asteroide {
    int x, y;           // Coordenadas del asteroide en la pantalla
    bool activo;        // Estado del asteroide (activo o inactivo)

    Asteroide(int x, int y); // Constructor que inicializa las coordenadas del asteroide
};

// Declaraciones de funciones relacionadas con el movimiento y dibujo de asteroides
void moverAsteroide(Asteroide& asteroide, vector<vector<char>>& pantalla); // Mueve el asteroide en la pantalla
void* ejecutarAsteroide(void* arg); // Ejecuta el movimiento del asteroide en un hilo
void dibujarPantallaAsteroides(const vector<Asteroide>& asteroides, vector<vector<char>>& pantalla); // Dibuja los asteroides en la pantalla

// Definir un carácter ASCII que representa un asteroide pequeño
const char ASTEROIDEC_ASCII = 'u';

// Estructura que representa un asteroide pequeño
struct Asteroidec {
    int x, y;          // Coordenadas del asteroide pequeño en la pantalla
    bool activo;       // Estado del asteroide pequeño (activo o inactivo)

    Asteroidec(int x, int y); // Constructor que inicializa las coordenadas del asteroide pequeño
};

// Declaraciones de funciones relacionadas con el movimiento y dibujo de asteroides pequeños
void moverAsteroidec(Asteroidec& asteroidec, vector<vector<char>>& pantalla); // Mueve el asteroide pequeño en la pantalla
void* ejecutarAsteroidec(void* arg); // Ejecuta el movimiento del asteroide pequeño en un hilo
void dibujarPantallaAsteroidesc(const vector<Asteroidec>& asteroidesc, vector<vector<char>>& pantalla); // Dibuja los asteroides pequeños en la pantalla

#endif  // Fin de la inclusión del encabezado
