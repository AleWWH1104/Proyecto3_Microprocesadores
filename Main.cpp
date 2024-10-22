
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
#include <conio.h> 

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

void dibujarUI(const Nave& nave1, const Nave& nave2, bool multijugador) {
    if (multijugador) {
        cout << "Jugador 1 - Vidas: " << nave1.vidas << "  Puntos: " << nave1.puntos << endl;
        cout << "Jugador 2 - Vidas: " << nave2.vidas << "  Puntos: " << nave2.puntos << endl;
    } else {
        cout << "Vidas: " << nave1.vidas << "  Puntos: " << nave1.puntos << endl;
    }
    cout << string(40, '-') << endl; 
}

void manejarEntradaJugadores(Nave& nave1, Nave& nave2, bool multijugador) {
    if (_kbhit()) {
        char tecla = _getch();
        moverNaveJugador1(nave1, tecla);
        if (multijugador) {
            int tecla2 = _getch();
            moverNaveJugador2(nave2, tecla2);
        }
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    bool multijugador = false;
    char modo;
    cout << "Selecciona el modo de juego (1: Solitario, 2: Multijugador): ";
    cin >> modo;
    if (modo == '2') {
        multijugador = true;
    }

    Nave nave1(columnas / 4, filas / 2, 3); 
    Nave nave2((3 * columnas) / 4, filas / 2, 3); 

    pthread_t hiloNave1, hiloNave2;
    pthread_create(&hiloNave1, nullptr, ejecutarNave, (void*)&nave1);
    if (multijugador) {
        pthread_create(&hiloNave2, nullptr, ejecutarNave, (void*)&nave2);
    }

    vector<pthread_t> hilosAsteroides(asteroides.size());
    for (size_t i = 0; i < asteroides.size(); ++i) {
        pthread_create(&hilosAsteroides[i], nullptr, ejecutarAsteroide, (void*)&asteroides[i]);
    }

    while (nave1.running && (!multijugador || nave2.running)) {
        borrar();
        limpiarPantalla(); 

        dibujarUI(nave1, nave2, multijugador);

        manejarEntradaJugadores(nave1, nave2, multijugador); 

        dibujarPantallaNave(nave1, pantalla);
        if (multijugador) {
            dibujarPantallaNave(nave2, pantalla);
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

    return 0;
}
