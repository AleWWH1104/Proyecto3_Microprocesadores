// Colision.cpp
#include "Colision.h"
#include "Nave.h"
#include "Asteroid.h"
#include <vector>
#include <iostream>
#include "AsteroidsGame.h"


using namespace std;
// Colision.cpp
extern const int filas;
extern const int columnas;


extern vector<vector<char>> pantalla;

int randomSign() {
    int randomValue = rand() % 2;
    return (randomValue == 0) ? -1 : 1;
}

// Función que verifica si la nave y un asteroide han colisionado
bool verificarColisionNaveAsteroide(const Nave& nave, const Asteroide& asteroide) {
    return (nave.x == asteroide.x && nave.y == asteroide.y);
}

// Funcion que detecta colisiones entre la nave y todos los asteroides (Para ambos jugadores)
void detectarColisionesNaveAsteroides(Nave& nave1, Nave* nave2, vector<Asteroide>& asteroides) {
    for (Asteroide& asteroide : asteroides) {
        if (asteroide.activo && verificarColisionNaveAsteroide(nave1, asteroide)) {
            cout << "Colisión detectada entre la nave 1 y un asteroide" << endl;
            nave1.vidas--;
            asteroide.activo = false;

            if (nave1.vidas <= 0) {
                nave1.running = false;
                cout << "Juego terminado, La nave 1 ha sido destruida." << endl;
            }
            break;
        }

        if (nave2 != nullptr && asteroide.activo && verificarColisionNaveAsteroide(*nave2, asteroide)) {
            cout << "Colisión detectada entre la nave 2 y un asteroide" << endl;
            nave2->vidas--;
            asteroide.activo = false;

            if (nave2->vidas <= 0) {
                nave2->running = false;
                cout << "Juego terminado, La nave 2 ha sido destruida." << endl;
            }
            break;
        }
    }
}

bool verificarColisionProyectilAsteroide(const Proyectil& proyectil, const Asteroide& asteroide) {
    return (proyectil.x == asteroide.x && proyectil.y == asteroide.y);
}

// Detección de colisiones para los proyectiles
void detectarColisionesProyectilAsteroides(Nave& nave1, Nave* nave2, std::vector<Proyectil>& proyectiles1, std::vector<Asteroide>& asteroides, std::vector<Asteroidec>& asteroidesc, std::vector<std::vector<char>>& pantalla) {
    for (Proyectil& proyectil : proyectiles1) {
        for (Asteroide& asteroide : asteroides) {
            if (asteroide.activo && verificarColisionProyectilAsteroide(proyectil, asteroide)) {
                std::cout << "Colisión detectada entre un proyectil de la nave 1 y un asteroide" << std::endl;
                nave1.puntos += 100;
                asteroide.activo = false;

                int x1 = asteroide.x - 1 >= 0 ? asteroide.x - 1 : pantalla[0].size() - 1;
                int y1 = asteroide.y - 1 >= 0 ? asteroide.y - 1 : pantalla.size() - 1;
                int x2 = asteroide.x + 1 < pantalla[0].size() ? asteroide.x + 1 : 0;
                int y2 = asteroide.y + 1 < pantalla.size() ? asteroide.y + 1 : 0;

                asteroidesc.emplace_back(x1, y1);  // Primer asteroide pequeño
                asteroidesc.emplace_back(x2, y2);  // Segundo asteroide pequeño
                break;
            }
        }
    }

    if (nave2 != nullptr) {
        for (Proyectil& proyectil : nave2->proyectiles) {
            for (Asteroide& asteroide : asteroides) {
                if (asteroide.activo && verificarColisionProyectilAsteroide(proyectil, asteroide)) {
                    std::cout << "Colisión detectada entre un proyectil de la nave 2 y un asteroide" << std::endl;
                    nave2->puntos += 100;
                    asteroide.activo = false;

                    int x1 = asteroide.x - 1 >= 0 ? asteroide.x - 1 : pantalla[0].size() - 1;
                    int y1 = asteroide.y - 1 >= 0 ? asteroide.y - 1 : pantalla.size() - 1;
                    int x2 = asteroide.x + 1 < pantalla[0].size() ? asteroide.x + 1 : 0;
                    int y2 = asteroide.y + 1 < pantalla.size() ? asteroide.y + 1 : 0;

                    asteroidesc.emplace_back(x1, y1);  // Primer asteroide pequeño
                    asteroidesc.emplace_back(x2, y2);  // Segundo asteroide pequeño
                    break;
                }
            }
        }
    }
}

bool verificarColisionNaveAsteroidec(const Nave& nave, const Asteroidec& asteroidec) {
    return (nave.x == asteroidec.x && nave.y == asteroidec.y);
}

// Función que detecta colisiones entre la nave y todos los asteroides pequeños (Para ambos jugadores)
void detectarColisionesNaveAsteroidesc(Nave& nave1, Nave* nave2, vector<Asteroidec>& asteroidesc) {
    for (Asteroidec& asteroidec : asteroidesc) {
        if (asteroidec.activo && verificarColisionNaveAsteroidec(nave1, asteroidec)) {
            cout << "Colisión detectada entre la nave 1 y un asteroide pequeño" << endl;
            nave1.vidas--;
            asteroidec.activo = false;

            if (nave1.vidas <= 0) {
                nave1.running = false;
                cout << "Juego terminado, La nave 1 ha sido destruida." << endl;
            }
            break;
        }

        if (nave2 != nullptr && asteroidec.activo && verificarColisionNaveAsteroidec(*nave2, asteroidec)) {
            cout << "Colisión detectada entre la nave 2 y un asteroide pequeño" << endl;
            nave2->vidas--;
            asteroidec.activo = false;

            if (nave2->vidas <= 0) {
                nave2->running = false;
                cout << "Juego terminado, La nave 2 ha sido destruida." << endl;
            }
            break;
        }
    }
}

bool verificarColisionProyectilAsteroidec(const Proyectil& proyectil, const Asteroidec& asteroidec) {
    return (proyectil.x == asteroidec.x && proyectil.y == asteroidec.y);
}

void detectarColisionesProyectilAsteroidesc(Nave& nave, std::vector<Proyectil>& proyectiles, std::vector<Asteroidec>& asteroidesc) {
    for (Proyectil& proyectil : proyectiles) {
        for (Asteroidec& asteroidec : asteroidesc) {
            if (asteroidec.activo && verificarColisionProyectilAsteroidec(proyectil, asteroidec)) {
                nave.puntos += 50;
                asteroidec.activo = false;
                break;
            }
        }
    }
}
