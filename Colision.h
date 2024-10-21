// Colision.h
#ifndef COLISION_H
#define COLISION_H

#include "Nave.h"
#include "Asteroid.h"
#include <vector>

// Verifica si la nave ha colisionado con un asteroide
bool verificarColisionNaveAsteroide(const Nave& nave, const Asteroide& asteroide);

// Detecta y maneja colisiones entre la nave y los asteroides
void detectarColisionesNaveAsteroides(Nave& nave, vector<Asteroide>& asteroides);

bool verificarColisionProyectilAsteroide(const Proyectil& proyectil, const Asteroide& asteroide);

void detectarColisionesProyectilAsteroides(Nave& nave, std::vector<Proyectil>& proyectiles, std::vector<Asteroide>& asteroides, std::vector<Asteroidec>& asteroidesc, std::vector<std::vector<char>>& pantalla);


bool verificarColisionNaveAsteroidec(const Nave& nave, const Asteroidec& asteroidec);

// Detecta y maneja colisiones entre la nave y los asteroides
void detectarColisionesNaveAsteroidesc(Nave& nave, vector<Asteroidec>& asteroidesc);

bool verificarColisionProyectilAsteroidec(const Proyectil& proyectil, const Asteroidec& asteroidec);

void detectarColisionesProyectilAsteroidesc(Nave& nave, std::vector<Proyectil>& proyectiles, std::vector<Asteroidec>& asteroidesc);


#endif // COLISION_H
