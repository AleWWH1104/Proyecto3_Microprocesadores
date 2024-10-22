
#include "Colision.h"
#include "Nave.h"
#include "Asteroid.h"
#include <vector>
#include <iostream>

using namespace std;

extern vector<vector<char>> pantalla;

int randomSign() {
    int randomValue = rand() % 2;
    return (randomValue == 0) ? -1 : 1;
}

bool verificarColisionNaveAsteroide(const Nave& nave, const Asteroide& asteroide) {
    return (nave.x == asteroide.x && nave.y == asteroide.y);
}

bool verificarColisionNaveAsteroidec(const Nave& nave, const Asteroidec& asteroidec) {
    return (nave.x == asteroidec.x && nave.y == asteroidec.y);
}

void detectarColisionesNaveAsteroides(Nave& nave1, Nave& nave2, vector<Asteroide>& asteroides) {
    for (Asteroide& asteroide : asteroides) {
        if (asteroide.activo) {
            if (verificarColisionNaveAsteroide(nave1, asteroide)) {
                nave1.restarVida();
                asteroide.activo = false;
                cout << "¡Colisión detectada entre la nave 1 y un asteroide!" << endl;
            }
            if (verificarColisionNaveAsteroide(nave2, asteroide)) {
                nave2.restarVida();
                asteroide.activo = false;
                cout << "¡Colisión detectada entre la nave 2 y un asteroide!" << endl;
            }
        }
    }
}

void detectarColisionesNaveAsteroidesc(Nave& nave1, Nave& nave2, vector<Asteroidec>& asteroidesc) {
    for (Asteroidec& asteroidec : asteroidesc) {
        if (asteroidec.activo) {
            if (verificarColisionNaveAsteroidec(nave1, asteroidec)) {
                nave1.restarVida();
                asteroidec.activo = false;
                cout << "¡Colisión detectada entre la nave 1 y un asteroide pequeño!" << endl;
            }
            if (verificarColisionNaveAsteroidec(nave2, asteroidec)) {
                nave2.restarVida();
                asteroidec.activo = false;
                cout << "¡Colisión detectada entre la nave 2 y un asteroide pequeño!" << endl;
            }
        }
    }
}

bool verificarColisionProyectilAsteroide(const Proyectil& proyectil, const Asteroide& asteroide) {
    return (proyectil.x == asteroide.x && proyectil.y == asteroide.y);
}

bool verificarColisionProyectilAsteroidec(const Proyectil& proyectil, const Asteroidec& asteroidec) {
    return (proyectil.x == asteroidec.x && proyectil.y == asteroidec.y);
}

void detectarColisionesProyectilAsteroides(Nave& nave, vector<Proyectil>& proyectiles, 
                                           vector<Asteroide>& asteroides, vector<Asteroidec>& asteroidesc, 
                                           vector<vector<char>>& pantalla) {
    for (Proyectil& proyectil : proyectiles) {
        if (proyectil.activo) {
            for (Asteroide& asteroide : asteroides) {
                if (asteroide.activo && verificarColisionProyectilAsteroide(proyectil, asteroide)) {
                    asteroide.activo = false;
                    proyectil.activo = false;
                    cout << "¡Proyectil ha destruido un asteroide!" << endl;
                }
            }
            for (Asteroidec& asteroidec : asteroidesc) {
                if (asteroidec.activo && verificarColisionProyectilAsteroidec(proyectil, asteroidec)) {
                    asteroidec.activo = false;
                    proyectil.activo = false;
                    cout << "¡Proyectil ha destruido un asteroide pequeño!" << endl;
                }
            }
        }
    }
}

void detectarColisionesProyectilAsteroidesc(Nave& nave, vector<Proyectil>& proyectiles, 
                                            vector<Asteroidec>& asteroidesc) {
    for (Proyectil& proyectil : proyectiles) {
        if (proyectil.activo) {
            for (Asteroidec& asteroidec : asteroidesc) {
                if (asteroidec.activo && verificarColisionProyectilAsteroidec(proyectil, asteroidec)) {
                    asteroidec.activo = false;
                    proyectil.activo = false;
                    cout << "¡Proyectil ha destruido un asteroide pequeño!" << endl;
                }
            }
        }
    }
}


void detectarColisionesProyectilAsteroides(Nave& nave1, Nave& nave2, vector<Asteroide>& asteroides) {
    for (Asteroide& asteroide : asteroides) {
        if (asteroide.activo) {
            // Verificar colisión con proyectiles de Jugador 1
            for (auto& proyectil : nave1.proyectiles) {
                if (proyectil.activo && proyectil.x == asteroide.x && proyectil.y == asteroide.y) {
                    proyectil.activo = false;
                    asteroide.activo = false;
                    nave1.puntos += 10; // Aumentar puntos para Jugador 1
                    cout << "Jugador 1 ha destruido un asteroide y ha ganado 10 puntos!" << endl;
                }
            }
            // Verificar colisión con proyectiles de Jugador 2
            for (auto& proyectil : nave2.proyectiles) {
                if (proyectil.activo && proyectil.x == asteroide.x && proyectil.y == asteroide.y) {
                    proyectil.activo = false;
                    asteroide.activo = false;
                    nave2.puntos += 10; // Aumentar puntos para Jugador 2
                    cout << "Jugador 2 ha destruido un asteroide y ha ganado 10 puntos!" << endl;
                }
            }
        }
    }
}
