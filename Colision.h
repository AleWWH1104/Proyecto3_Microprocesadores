
#ifndef COLISION_H
#define COLISION_H

#include "Nave.h"
#include "Asteroid.h"
#include <vector>

// Verifica si una nave ha colisionado con un asteroide
bool verificarColisionNaveAsteroide(const Nave& nave, const Asteroide& asteroide);

// Detecta y maneja colisiones entre las naves y los asteroides
void detectarColisionesNaveAsteroides(Nave& nave1, Nave& nave2, vector<Asteroide>& asteroides);

// Verifica colisión entre un proyectil y un asteroide
bool verificarColisionProyectilAsteroide(const Proyectil& proyectil, const Asteroide& asteroide);

#endif 
