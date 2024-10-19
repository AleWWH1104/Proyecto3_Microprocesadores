// Colision.cpp
#include "Colision.h"
#include "Nave.h"
#include "Asteroid.h"
#include <vector>
#include <iostream>

using namespace std;

// Función que verifica si la nave y un asteroide han colisionado
bool verificarColisionNaveAsteroide(const Nave& nave, const Asteroide& asteroide) {
    //la colision ocurre si las coordenadas de la nave coinciden con las del asteroide
    return (nave.x == asteroide.x && nave.y == asteroide.y);
}

//Funcion que detecta colisiones entre la nave y todos los asteroides
void detectarColisionesNaveAsteroides(Nave& nave, vector<Asteroide>& asteroides) {
    for (Asteroide& asteroide : asteroides) {
        if (asteroide.activo && verificarColisionNaveAsteroide(nave, asteroide)) {
            cout << "¡Colisión detectada entre la nave y un asteroide!" << endl;
            
            // Restar una vida al jugador
            nave.vidas--;

            // Desactivar el asteroide (o realizar otra acción, como dividirlo si es grande)
            asteroide.activo = false;

            //si pierde 
            if (nave.vidas <= 0) {
                nave.running = false; // Detener el juego si la nave se queda sin vidas
                cout << "¡Juego terminado! La nave ha sido destruida." << endl;
            }

            break;  // No es necesario seguir buscando otras colisiones en este ciclo
        }
    }
}
