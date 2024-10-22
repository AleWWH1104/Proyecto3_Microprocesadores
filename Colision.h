
#ifndef COLISION_H
#define COLISION_H

#include "Nave.h"
#include "Asteroid.h"
#include "Proyectil.h"  // Añadir esta línea
#include <vector>

bool verificarColisionNaveAsteroide(const Nave& nave, const Asteroide& asteroide);
void detectarColisionesNaveAsteroides(Nave& nave1, Nave* nave2, vector<Asteroide>& asteroides);

bool verificarColisionProyectilAsteroide(const Proyectil& proyectil, const Asteroide& asteroide);
void detectarColisionesProyectilAsteroides(Nave& nave1, Nave* nave2, std::vector<Proyectil>& proyectiles1, std::vector<Asteroide>& asteroides, std::vector<Asteroidec>& asteroidesc, std::vector<std::vector<char>>& pantalla);

bool verificarColisionNaveAsteroidec(const Nave& nave, const Asteroidec& asteroidec);
void detectarColisionesNaveAsteroidesc(Nave& nave1, Nave* nave2, std::vector<Asteroidec>& asteroidesc);

bool verificarColisionProyectilAsteroidec(const Proyectil& proyectil, const Asteroidec& asteroidec);
void detectarColisionesProyectilAsteroidesc(Nave& nave, std::vector<Proyectil>& proyectiles, std::vector<Asteroidec>& asteroidesc);

#endif // COLISION_H
