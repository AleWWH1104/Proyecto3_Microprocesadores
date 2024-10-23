// Colision.h
#ifndef COLISION_H    // Evita la inclusión múltiple del encabezado
#define COLISION_H

#include "Nave.h"        // Incluir el encabezado que define la estructura de la nave
#include "Asteroid.h"    // Incluir el encabezado que define las estructuras de asteroides
#include <vector>        // Incluir la biblioteca para usar vectores estándar

// Verifica si la nave ha colisionado con un asteroide
bool verificarColisionNaveAsteroide(const Nave& nave, const Asteroide& asteroide);

// Detecta y maneja colisiones entre la nave y los asteroides
void detectarColisionesNaveAsteroides(Nave& nave, std::vector<Asteroide>& asteroides);

// Verifica si un proyectil ha colisionado con un asteroide
bool verificarColisionProyectilAsteroide(const Proyectil& proyectil, const Asteroide& asteroide);

// Detecta colisiones entre los proyectiles y los asteroides, y maneja sus consecuencias
void detectarColisionesProyectilAsteroides(Nave& nave, std::vector<Proyectil>& proyectiles, std::vector<Asteroide>& asteroides, std::vector<Asteroidec>& asteroidesc, std::vector<std::vector<char>>& pantalla);

// Verifica si la nave ha colisionado con un asteroide pequeño
bool verificarColisionNaveAsteroidec(const Nave& nave, const Asteroidec& asteroidec);

// Detecta y maneja colisiones entre la nave y los asteroides pequeños
void detectarColisionesNaveAsteroidesc(Nave& nave, std::vector<Asteroidec>& asteroidesc);

// Verifica si un proyectil ha colisionado con un asteroide pequeño
bool verificarColisionProyectilAsteroidec(const Proyectil& proyectil, const Asteroidec& asteroidec);

// Detecta colisiones entre los proyectiles y los asteroides pequeños, y maneja sus consecuencias
void detectarColisionesProyectilAsteroidesc(Nave& nave, std::vector<Proyectil>& proyectiles, std::vector<Asteroidec>& asteroidesc);

#endif // COLISION_H
