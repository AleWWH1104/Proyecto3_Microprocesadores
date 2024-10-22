
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

bool verificarColisionProyectilAsteroide(const Proyectil& proyectil, const Asteroide& asteroide) {
    return (proyectil.x == asteroide.x && proyectil.y == asteroide.y);
}
