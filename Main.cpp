
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

void dibujarProyectiles(const vector<Proyectil>& proyectiles, vector<vector<char>>& pantalla) {
    for (const auto& proyectil : proyectiles) {
        if (proyectil.activo) {
            pantalla[proyectil.y][proyectil.x] = '*'; 
        }
    }
}

int cantAsteroidesc = asteroides.size() * 2;

int main() {
    srand(static_cast<unsigned int>(time(0))); 

    int seleccion;
    bool multijugador = false;

    cout << "Selecciona el modo de juego:" << endl;
    cout << "1. Solitario" << endl;
    cout << "2. Multijugador" << endl;
    cout << "Elige una opcion: ";
    cin >> seleccion;
    if (seleccion == 2) {
        multijugador = true;
    }

    Nave nave1(columnas / 2, filas / 2, 3); 
    Nave nave2(columnas / 3, filas / 3, 3); 
    vector<Asteroide> asteroides; 
    vector<Asteroidec> asteroidesc;

    for (int i = 0; i < 5; ++i) {
        asteroides.emplace_back(rand() % columnas, rand() % filas); 
    }

    pthread_t hiloNave1;
    pthread_create(&hiloNave1, nullptr, ejecutarNave, (void*)&nave1);

    pthread_t hiloNave2;
    if (multijugador) {
        pthread_create(&hiloNave2, nullptr, ejecutarNave, (void*)&nave2);
    }

    vector<pthread_t> hilosAsteroides(asteroides.size());
    for (size_t i = 0; i < asteroides.size(); ++i) {
        pthread_create(&hilosAsteroides[i], nullptr, ejecutarAsteroide, (void*)&asteroides[i]);
    }

    vector<pthread_t> hilosAsteroidesc(cantAsteroidesc);
    for (size_t i = 0; i < cantAsteroidesc; ++i) {
        pthread_create(&hilosAsteroidesc[i], nullptr, ejecutarAsteroidec, (void*)&asteroidesc[i]);
    }

    while (nave1.running) {
        borrar();
        limpiarPantalla();

        dibujarUI(nave1);

        moverProyectiles(nave1.proyectiles);
        if (multijugador) {
            moverProyectiles(nave2.proyectiles);
        }

        for (Asteroidec& asteroidec : asteroidesc) {
            if (asteroidec.activo) {
                moverAsteroidec(asteroidec, pantalla);
            }
        }
        
        dibujarPantallaNave(nave1, pantalla);
        if (multijugador) {
            dibujarPantallaNave(nave2, pantalla);
        }
        
        dibujarPantallaAsteroides(asteroides, pantalla);
        dibujarProyectiles(nave1.proyectiles, pantalla);
        if (multijugador) {
            dibujarProyectiles(nave2.proyectiles, pantalla);
        }
        
        dibujarPantallaAsteroidesc(asteroidesc, pantalla);

        // Revisar la firma de estas funciones y asegurarse de que se encuentren definidas correctamente
        detectarColisionesNaveAsteroides(nave1, nave2, asteroides);
        if (multijugador) {
            detectarColisionesNaveAsteroides(nave1, nave2, asteroides);
        }

        detectarColisionesProyectilAsteroides(nave1, nave1.proyectiles, asteroides, asteroidesc, pantalla);
        if (multijugador) {
            detectarColisionesProyectilAsteroides(nave2, nave2.proyectiles, asteroides, asteroidesc, pantalla);
        }

        detectarColisionesNaveAsteroidesc(nave1, nave2, asteroidesc);
        if (multijugador) {
            detectarColisionesNaveAsteroidesc(nave2, nave1, asteroidesc);
        }

        detectarColisionesProyectilAsteroidesc(nave1, nave1.proyectiles, asteroidesc);
        if (multijugador) {
            detectarColisionesProyectilAsteroidesc(nave2, nave2.proyectiles, asteroidesc);
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
    if (multijugador) {
        pthread_join(hiloNave2, nullptr);
    }
    for (auto& hilo : hilosAsteroides) {
        pthread_join(hilo, nullptr);
    }

    return 0;
}
