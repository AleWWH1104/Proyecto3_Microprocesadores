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

const int filas = 20;          // Número de filas de la pantalla
const int columnas = 40;       // Número de columnas de la pantalla

vector<vector<char>> pantalla(filas, vector<char>(columnas, ' ')); // Matriz para representar la pantalla
vector<Asteroide> asteroides;  // Vector para almacenar asteroides

// Función para limpiar la pantalla de juego
void limpiarPantalla() {
    for (auto& fila : pantalla) {
        fill(fila.begin(), fila.end(), ' '); // Rellenar cada fila con espacios en blanco
    }
}

// Función para borrar la consola
void borrar() {
#ifdef _WIN32
    system("cls");  // Limpiar pantalla en Windows
#else
    system("clear");  // Limpiar pantalla en Linux/Unix
#endif
}

// Función para dibujar la interfaz de usuario
void dibujarUI(const Nave& nave1, const Nave* nave2 = nullptr) {
    cout << "Jugador 1 - Vidas: " << nave1.vidas << "   Puntos: " << nave1.puntos << endl;
    if (nave2) {
        cout << "Jugador 2 - Vidas: " << nave2->vidas << endl;
    }
    cout << string(40, '-') << endl; // Línea divisoria
}

// Mueve los proyectiles en la pantalla
void moverProyectiles(vector<Proyectil>& proyectiles) {
    for (auto& proyectil : proyectiles) {  
        if (proyectil.activo) {  
            switch (proyectil.direccion) {
                case 0: proyectil.y -= 1; break; // Arriba
                case 1: proyectil.x += 1; break; // Derecha
                case 2: proyectil.y += 1; break; // Abajo
                case 3: proyectil.x -= 1; break; // Izquierda
            }
            // Desactivar el proyectil si sale de los límites de la pantalla
            if (proyectil.y < 0 || proyectil.y >= filas || proyectil.x < 0 || proyectil.x >= columnas) {
                proyectil.activo = false; 
            }
        }
    }
}

// Dibuja los proyectiles en la pantalla
void dibujarProyectiles(const vector<Proyectil>& proyectiles, vector<vector<char>>& pantalla) {
    for (const auto& proyectil : proyectiles) {
        if (proyectil.activo) {
            pantalla[proyectil.y][proyectil.x] = '*'; // Representar el proyectil
        }
    }
}

int cantAsteroidesc = asteroides.size() * 2; // Cantidad de asteroides pequeños a crear

int main() {
    srand(static_cast<unsigned int>(time(0))); // Semilla para generar números aleatorios

    int modo;
    cout << "Seleccione el modo de juego: 1 para un jugador, 2 para dos jugadores: ";
    cin >> modo;

    Nave* nave1 = new Nave(columnas / 4, filas / 2, 3, true); // Inicializar la nave del jugador 1
    Nave* nave2 = nullptr;

    if (modo == 2) {
        nave2 = new Nave(columnas * 3 / 4, filas / 2, 3, false); // Inicializar la nave del jugador 2
    }

    vector<Asteroide> asteroides; // Vector de asteroides grandes
    vector<Asteroidec> asteroidesc; // Vector de asteroides pequeños

    // Crear asteroides en posiciones aleatorias
    for (int i = 0; i < 10; ++i) {
        asteroides.emplace_back(rand() % columnas, rand() % filas); // Posiciones aleatorias
    }

    pthread_t hiloNave1, hiloNave2;
    pthread_create(&hiloNave1, nullptr, ejecutarNave, (void*)nave1); // Crear hilo para la nave 1
    if (modo == 2) {
        pthread_create(&hiloNave2, nullptr, ejecutarNave, (void*)nave2); // Crear hilo para la nave 2
    }

    vector<pthread_t> hilosAsteroides(asteroides.size());
    for (size_t i = 0; i < asteroides.size(); ++i) {
        pthread_create(&hilosAsteroides[i], nullptr, ejecutarAsteroide, (void*)&asteroides[i]); // Hilos para asteroides
    }

    vector<pthread_t> hilosAsteroidesc(cantAsteroidesc);
    for (size_t i = 0; i < cantAsteroidesc; ++i) {
        pthread_create(&hilosAsteroidesc[i], nullptr, ejecutarAsteroidec, (void*)&asteroidesc[i]); // Hilos para asteroides pequeños
    }

    // Bucle principal del juego
    while (nave1->running || (modo == 2 && nave2->running)) {
        borrar(); // Limpiar pantalla
        limpiarPantalla(); // Limpiar pantalla de juego

        // Dibujar interfaz de usuario
        if (modo == 2) {
            dibujarUI(*nave1, nave2);
        } else {
            dibujarUI(*nave1);
        }
        
        moverProyectiles(nave1->proyectiles); // Mover proyectiles de la nave 1
        if (modo == 2) {
            moverProyectiles(nave2->proyectiles); // Mover proyectiles de la nave 2
        }

        // Mover asteroides pequeños
        for (Asteroidec& asteroidec : asteroidesc) {
            if (asteroidec.activo) {
                moverAsteroidec(asteroidec, pantalla);
            }
        }

        // Dibujar la pantalla
        dibujarPantallaNave(*nave1, pantalla); 
        if (modo == 2) {
            dibujarPantallaNave(*nave2, pantalla);
        }
        dibujarPantallaAsteroides(asteroides, pantalla);
        dibujarProyectiles(nave1->proyectiles, pantalla); 
        if (modo == 2) {
            dibujarProyectiles(nave2->proyectiles, pantalla);
        }
        dibujarPantallaAsteroidesc(asteroidesc, pantalla);

        // Verificar colisiones
        detectarColisionesNaveAsteroides(*nave1, asteroides);
        if (modo == 2) {
            detectarColisionesNaveAsteroides(*nave2, asteroides);
        }

        detectarColisionesProyectilAsteroides(*nave1, nave1->proyectiles, asteroides, asteroidesc, pantalla);
        if (modo == 2) {
            detectarColisionesProyectilAsteroides(*nave2, nave2->proyectiles, asteroides, asteroidesc, pantalla);
        }

        detectarColisionesNaveAsteroidesc(*nave1, asteroidesc);
        if (modo == 2) {
            detectarColisionesNaveAsteroidesc(*nave2, asteroidesc);
        }

        detectarColisionesProyectilAsteroidesc(*nave1, nave1->proyectiles, asteroidesc);
        if (modo == 2) {
            detectarColisionesProyectilAsteroidesc(*nave2, nave2->proyectiles, asteroidesc);
        }

        // Verificar la condición de finalización del juego por puntos
        if ((modo == 1 && nave1->puntos >= 600) || (modo == 2 && (nave1->puntos + (nave2 ? nave2->puntos : 0)) >= 1000)) {
            cout << "   YEII, Felicidades. Has alcanzado la puntuacion objetivo. Fin del juego." << endl;
            break; // Salir del bucle si se alcanzan los puntos necesarios
        }

        // Dibujar la pantalla
        for (const auto& fila : pantalla) {
            for (char celda : fila) {
                cout << celda; // Mostrar cada celda de la pantalla
            }
            cout << endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Esperar un tiempo para la siguiente iteración
    }

    // Esperar a que terminen los hilos
    pthread_join(hiloNave1, nullptr);
    if (modo == 2) {
        pthread_join(hiloNave2, nullptr);
    }
    for (auto& hilo : hilosAsteroides) {
        pthread_join(hilo, nullptr);
    }

    // Liberar memoria
    delete nave1;
    if (nave2) delete nave2;

    return 0; // Finaliza el programa
}
