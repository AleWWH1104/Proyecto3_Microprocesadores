#include <iostream>
#include <pthread.h>
#include <vector>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include "Nave.h"      // Incluir la cabecera de Nave
#include "Asteroid.h"  // Incluir la cabecera de Asteroid

using namespace std;

// Tamaño de la pantalla
const int filas = 20;     // Número de filas
const int columnas = 40;  // Número de columnas

// Pantalla donde se dibujan la nave y los asteroides
vector<vector<char>> pantalla(filas, vector<char>(columnas, ' '));

// Función para limpiar la pantalla
void limpiarPantalla() {
    for (auto& fila : pantalla) {
        fill(fila.begin(), fila.end(), ' '); // Limpiar pantalla
    }
}

// Función principal del juego
int main() {
    srand(static_cast<unsigned int>(time(0))); // Semilla para aleatoriedad

    Nave nave(columnas / 2, filas / 2); // Crear la nave en el centro de la pantalla
    vector<Asteroide> asteroides; // Vector para almacenar los asteroides

    // Inicializar algunos asteroides
    for (int i = 0; i < 5; ++i) {
        asteroides.emplace_back(rand() % columnas, rand() % filas); // Crear asteroides en posiciones aleatorias
    }

    // Crear hilo para la nave
    pthread_t hiloNave;
    pthread_create(&hiloNave, nullptr, ejecutarNave, (void*)&nave);

    // Crear hilos para los asteroides
    vector<pthread_t> hilosAsteroides(asteroides.size());
    for (size_t i = 0; i < asteroides.size(); ++i) {
        pthread_create(&hilosAsteroides[i], nullptr, ejecutarAsteroide, (void*)&asteroides[i]);
    }

    // Bucle principal del juego
    while (nave.running) {
        limpiarPantalla(); // Limpiar la pantalla
        dibujarPantallaNave(nave, pantalla); // Dibujar la nave
        dibujarPantallaAsteroides(asteroides, pantalla); // Dibujar asteroides

        // Mostrar la pantalla en la consola
        for (const auto& fila : pantalla) {
            for (char celda : fila) {
                cout << celda; // Imprimir cada celda
            }
            cout << endl; // Nueva línea después de cada fila
        }

        usleep(100000); // Pausa para controlar la velocidad del juego
    }

    // Esperar a que los hilos terminen
    pthread_join(hiloNave, nullptr);
    for (auto& hilo : hilosAsteroides) {
        pthread_join(hilo, nullptr);
    }

    return 0;
}
