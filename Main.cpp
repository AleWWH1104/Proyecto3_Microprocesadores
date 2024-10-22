
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
int filas = 20;     // Número de filas
int columnas = 40;  // Número de columnas

// Pantalla donde se dibujan las naves y los asteroides
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

void dibujarUI(const Nave& nave1, const Nave* nave2 = nullptr) {
    cout << "Jugador 1 - Vidas: " << nave1.vidas << "  Puntos: " << nave1.puntos;
    if (nave2) {
        cout << "   Jugador 2 - Vidas: " << nave2->vidas << "  Puntos: " << nave2->puntos;
    }
    cout << endl;
    cout << string(40, '-') << endl;
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

// Función para seleccionar el modo de juego
int seleccionarModo() {
    int opcion;
    do {
        cout << "Selecciona el modo de juego:" << endl;
        cout << "1. Un jugador" << endl;
        cout << "2. Dos jugadores" << endl;
        cout << "Opción: ";
        cin >> opcion;
    } while (opcion != 1 && opcion != 2);
    return opcion;
}

// Función principal del juego
int main() {
    srand(static_cast<unsigned int>(time(0))); // Semilla para aleatoriedad

    // Seleccionar el modo de juego
    int modo = seleccionarModo();

    // Crear naves para los jugadores
    Nave nave1(columnas / 2, filas / 2, 3);
    Nave nave2(columnas / 2 - 10, filas / 2, 3); // Segunda nave para el segundo jugador

    bool esMultijugador = (modo == 2);

    // Inicializar algunos asteroides
    for (int i = 0; i < 5; ++i) {
        asteroides.emplace_back(rand() % columnas, rand() % filas); // Crear asteroides en posiciones aleatorias
    }

    vector<Asteroidec> asteroidesc;

    // Crear hilo para la nave 1
    pthread_t hiloNave1, hiloNave2;
    pthread_create(&hiloNave1, nullptr, ejecutarNave, (void*)&nave1);

    // Crear hilo para la nave 2 si el modo es multijugador
    if (esMultijugador) {
        pthread_create(&hiloNave2, nullptr, ejecutarNave, (void*)&nave2);
    }

    // Crear hilos para los asteroides
    vector<pthread_t> hilosAsteroides(asteroides.size());
    for (size_t i = 0; i < asteroides.size(); ++i) {
        pthread_create(&hilosAsteroides[i], nullptr, ejecutarAsteroide, (void*)&asteroides[i]);
    }

    // Crear hilos para los asteroides pequeños
    vector<pthread_t> hilosAsteroidesc(asteroides.size() * 2);
    for (size_t i = 0; i < asteroidesc.size(); ++i) {
        pthread_create(&hilosAsteroidesc[i], nullptr, ejecutarAsteroidec, (void*)&asteroidesc[i]);
    }

    // Bucle principal del juego
    while (nave1.running || (esMultijugador && nave2.running)) {
        borrar();
        limpiarPantalla(); // Limpiar la pantalla

        // Dibujar el UI
        if (esMultijugador) {
            dibujarUI(nave1, &nave2);
        } else {
            dibujarUI(nave1);
        }

        // Mover proyectiles
        moverProyectiles(nave1.proyectiles);
        if (esMultijugador) {
            moverProyectiles(nave2.proyectiles);
        }

        // Mover asteroides pequeños
        for (Asteroidec& asteroidec : asteroidesc) {
            if (asteroidec.activo) {
                moverAsteroidec(asteroidec, pantalla);
            }
        }
        
        // Dibujar la nave y los asteroides
        dibujarPantallaNave(nave1, pantalla); 
        if (esMultijugador) {
            dibujarPantallaNave(nave2, pantalla);
        }
        
        dibujarPantallaAsteroides(asteroides, pantalla);
        dibujarProyectiles(nave1.proyectiles, pantalla); // Dibujar los proyectiles
        if (esMultijugador) {
            dibujarProyectiles(nave2.proyectiles, pantalla); // Dibujar proyectiles de nave2
        }

        dibujarPantallaAsteroidesc(asteroidesc, pantalla);

        // Verificar colisiones entre la nave y los asteroides
        detectarColisionesNaveAsteroides(nave1, esMultijugador ? &nave2 : nullptr, asteroides);
        if (esMultijugador && nave2.running) { detectarColisionesNaveAsteroides(nave2, nullptr, asteroides); }

        detectarColisionesProyectilAsteroides(nave1, esMultijugador ? &nave2 : nullptr, nave1.proyectiles, asteroides, asteroidesc, pantalla);

        if (esMultijugador) {
            detectarColisionesProyectilAsteroides(nave2, nullptr, nave2.proyectiles, asteroides, asteroidesc, pantalla);
        }

        detectarColisionesNaveAsteroidesc(nave1, &nave2, asteroidesc);

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
    pthread_join(hiloNave1, nullptr);
    if (esMultijugador) {
        pthread_join(hiloNave2, nullptr);
    }
    for (auto& hilo : hilosAsteroides) {
        pthread_join(hilo, nullptr);
    }

    return 0;
}
