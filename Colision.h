
#ifndef COLISION_H
#define COLISION_H

#include "Nave.h"
#include "Asteroid.h"
#include <vector>

// Verifica si una nave ha colisionado con un asteroide
bool verificarColisionNaveAsteroide(const Nave& nave, const Asteroide& asteroide);
bool verificarColisionNaveAsteroidec(const Nave& nave, const Asteroidec& asteroidec); // Nueva función

// Detecta y maneja colisiones entre las naves y los asteroides
void detectarColisionesNaveAsteroides(Nave& nave1, Nave& nave2, std::vector<Asteroide>& asteroides);
void detectarColisionesNaveAsteroidesc(Nave& nave1, Nave& nave2, std::vector<Asteroidec>& asteroidesc); // Nueva función

// Verifica colisión entre un proyectil y un asteroide
bool verificarColisionProyectilAsteroide(const Proyectil& proyectil, const Asteroide& asteroide);
bool verificarColisionProyectilAsteroidec(const Proyectil& proyectil, const Asteroidec& asteroidec); // Nueva función

void detectarColisionesProyectilAsteroides(Nave& nave, std::vector<Proyectil>& proyectiles, 
                                           std::vector<Asteroide>& asteroides, std::vector<Asteroidec>& asteroidesc, 
                                           std::vector<std::vector<char>>& pantalla);

void detectarColisionesProyectilAsteroidesc(Nave& nave, std::vector<Proyectil>& proyectiles, 
                                            std::vector<Asteroidec>& asteroidesc);

#endif
