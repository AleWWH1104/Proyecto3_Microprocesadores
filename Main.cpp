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

const int filas = 20;
const int columnas = 40;

vector<vector<char>> pantalla(filas, vector<char>(columnas, ' '));

vector<Asteroide> asteroides;

void limpiarPantalla() {
    for (auto& fila : pantalla) {
        fill(fila.begin(), fila.end(), ' '); // Limpiar pantalla
    }
}

void borrar() {
#ifdef _WIN32
    system("cls");  // Limpiar pantalla en Windows
#else
    system("clear");  // Limpiar pantalla en Linux/Unix
#endif
}

void dibujarUI(const Nave& nave1, const Nave* nave2 = nullptr) {
    cout << "Jugador 1 - Vidas: " << nave1.vidas << "   Puntos: " << nave1.puntos << endl;
    if (nave2) {
        cout << "Jugador 2 - Vidas: " << nave2->vidas << endl;
    }
    cout << string(40, '-') << endl; // Línea divisoria
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

int cantAsteroidesc = asteroides.size() * 2;

int main() {
    srand(static_cast<unsigned int>(time(0))); // Semilla para aleatoriedad

    int modo;
    cout << "Seleccione el modo de juego: 1 para un jugador, 2 para dos jugadores: ";
    cin >> modo;

    Nave* nave1 = new Nave(columnas / 4, filas / 2, 3, true); // Nave del jugador 1
    Nave* nave2 = nullptr;

    if (modo == 2) {
        nave2 = new Nave(columnas * 3 / 4, filas / 2, 3, false); // Nave del jugador 2
    }

    vector<Asteroide> asteroides;
    vector<Asteroidec> asteroidesc;

    for (int i = 0; i < 10; ++i) {
        asteroides.emplace_back(rand() % columnas, rand() % filas); // Crear asteroides en posiciones aleatorias
    }

    pthread_t hiloNave1, hiloNave2;
    pthread_create(&hiloNave1, nullptr, ejecutarNave, (void*)nave1);
    if (modo == 2) {
        pthread_create(&hiloNave2, nullptr, ejecutarNave, (void*)nave2);
    }

    vector<pthread_t> hilosAsteroides(asteroides.size());
    for (size_t i = 0; i < asteroides.size(); ++i) {
        pthread_create(&hilosAsteroides[i], nullptr, ejecutarAsteroide, (void*)&asteroides[i]);
    }

    vector<pthread_t> hilosAsteroidesc(cantAsteroidesc);
    for (size_t i = 0; i < cantAsteroidesc; ++i) {
        pthread_create(&hilosAsteroidesc[i], nullptr, ejecutarAsteroidec, (void*)&asteroidesc[i]);
    }

    while (nave1->running || (modo == 2 && nave2->running)) {
        borrar();
        limpiarPantalla();

        if (modo == 2) {
            dibujarUI(*nave1, nave2);
        } else {
            dibujarUI(*nave1);
        }
        
        moverProyectiles(nave1->proyectiles);
        if (modo == 2) {
            moverProyectiles(nave2->proyectiles);
        }

        for (Asteroidec& asteroidec : asteroidesc) {
            if (asteroidec.activo) {
                moverAsteroidec(asteroidec, pantalla);
            }
        }

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
            break;
        }

        for (const auto& fila : pantalla) {
            for (char celda : fila) {
                cout << celda; 
            }
            cout << endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    pthread_join(hiloNave1, nullptr);
    if (modo == 2) {
        pthread_join(hiloNave2, nullptr);
    }
    for (auto& hilo : hilosAsteroides) {
        pthread_join(hilo, nullptr);
    }

    delete nave1;
    if (nave2) delete nave2;

    return 0;
}
