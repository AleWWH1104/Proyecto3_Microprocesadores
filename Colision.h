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

#endif // COLISION_H
