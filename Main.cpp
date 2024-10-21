#include <iostream>
#include <pthread.h>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "Nave.h"      // Incluir la cabecera de Nave
#include "Asteroid.h"  // Incluir la cabecera de Asteroid
#include <thread> 

#include "Colision.h"

using namespace std;

// Tamaño de la pantalla
const int filas = 20;     // Número de filas
const int columnas = 40;  // Número de columnas

// Pantalla donde se dibujan la nave y los asteroides
vector<vector<char>> pantalla(filas, vector<char>(columnas, ' '));

vector<Asteroide> asteroides; // Declara el vector de asteroides

// Función para limpiar la pantalla
void limpiarPantalla() {
    for (auto& fila : pantalla) {
        fill(fila.begin(), fila.end(), ' '); // Limpiar pantalla
    }
}

// Función para que se borre todo lo que esta en al pantalla
void borrar() {
#ifdef _WIN32
    system("cls");  // Limpiar pantalla en Windows
#else
    system("clear");  // Limpiar pantalla en Linux/Unix
#endif
}

void dibujarUI(const Nave& nave) {
    cout << "Vidas: " << nave.vidas<< "                 Puntos: " << nave.puntos << endl; // Mostrar vidas
    cout << string(40, '-') << endl; // Línea divisoria
}

void moverProyectiles(vector<Proyectil>& proyectiles) {
    for (auto& proyectil : proyectiles) {  
        if (proyectil.activo) {  
            // Mover el proyectil en la dirección actual
            switch (proyectil.direccion) {  // Asegúrate de que la dirección esté almacenada en el proyectil
                case 0: proyectil.y -= 1; break; // Arriba
                case 1: proyectil.x += 1; break; // Derecha
                case 2: proyectil.y += 1; break; // Abajo
                case 3: proyectil.x -= 1; break; // Izquierda
            }

            // Verificar si el proyectil sale de la pantalla
            if (proyectil.y < 0 || proyectil.y >= filas || proyectil.x < 0 || proyectil.x >= columnas) {
                proyectil.activo = false; // Desactivar si sale de la pantalla
            }
        }
    }
}

void dibujarProyectiles(const vector<Proyectil>& proyectiles, vector<vector<char>>& pantalla) {
    for (const auto& proyectil : proyectiles) {
        if (proyectil.activo) {
            pantalla[proyectil.y][proyectil.x] = '*'; // Representar el proyectil
        }
    }
}

int cantAsteroidesc = asteroides.size() * 2; // Usa el tamaño del vector






// Función principal del juego
int main() {
    srand(static_cast<unsigned int>(time(0))); // Semilla para aleatoriedad

    Nave nave(columnas / 2, filas / 2, 3); // Crear la nave en el centro de la pantalla con 3 vidas
    vector<Asteroide> asteroides; // Vector para almacenar los asteroides
    vector<Asteroidec> asteroidesc;

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

    // Crear hilos para los asteroides pequeños
    vector<pthread_t> hilosAsteroidesc(cantAsteroidesc);
    for (size_t i = 0; i < cantAsteroidesc; ++i) {
        pthread_create(&hilosAsteroidesc[i], nullptr, ejecutarAsteroidec, (void*)&asteroidesc[i]);
    }


    // Bucle principal del juego
    while (nave.running) {
        borrar();
        limpiarPantalla(); // Limpiar la pantalla

        // Dibujar el UI
        dibujarUI(nave);

        // Mover proyectiles
        moverProyectiles(nave.proyectiles);
        
        // Dibujar la nave y los asteroides
        dibujarPantallaNave(nave, pantalla); 
        dibujarPantallaAsteroides(asteroides, pantalla);
        dibujarProyectiles(nave.proyectiles, pantalla); // Dibujar los proyectiles

        dibujarPantallaAsteroidesc(asteroidesc, pantalla);


        // Verificar colisiones entre la nave y los asteroides
        detectarColisionesNaveAsteroides(nave, asteroides);
        
        
        detectarColisionesProyectilAsteroides(nave, nave.proyectiles, asteroides, asteroidesc, pantalla);




        // Mostrar la pantalla en la consola
        for (const auto& fila : pantalla) {
            for (char celda : fila) {
                cout << celda; // Imprimir cada celda
            }
            cout << endl; // Nueva línea después de cada fila
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    // Esperar a que los hilos terminen
    pthread_join(hiloNave, nullptr);
    for (auto& hilo : hilosAsteroides) {
        pthread_join(hilo, nullptr);
    }

    return 0;
}
