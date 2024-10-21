// Colision.cpp
#include "Colision.h"
#include "Nave.h"
#include "Asteroid.h"
#include <vector>
#include <iostream>

using namespace std;

extern vector<vector<char>> pantalla;


int randomSign() {
    // Generar un número aleatorio, 0 o 1
    int randomValue = rand() % 2;
    
    // Si es 0, devolver -1, si es 1, devolver 1
    return (randomValue == 0) ? -1 : 1;
}

// Función que verifica si la nave y un asteroide han colisionado
bool verificarColisionNaveAsteroide(const Nave& nave, const Asteroide& asteroide) {
    //la colision ocurre si las coordenadas de la nave coinciden con las del asteroide
    return (nave.x == asteroide.x && nave.y == asteroide.y);
}

//Funcion que detecta colisiones entre la nave y todos los asteroides
void detectarColisionesNaveAsteroides(Nave& nave, vector<Asteroide>& asteroides) {
    for (Asteroide& asteroide : asteroides) {
        if (asteroide.activo && verificarColisionNaveAsteroide(nave, asteroide)) {
            cout << "Colision detectada entre la nave y un asteroide" << endl;
            
            // Restar una vida al jugador
            nave.vidas--;

            // Desactivar el asteroide (o realizar otra acción, como dividirlo si es grande)
            asteroide.activo = false;

            //si pierde 
            if (nave.vidas <= 0) {
                nave.running = false; // Detener el juego si la nave se queda sin vidas
                cout << "Juego terminado, La nave ha sido destruida." << endl;
            }

            break;  // No es necesario seguir buscando otras colisiones en este ciclo
        }
    }
}


bool verificarColisionProyectilAsteroide(const Proyectil& proyectil, const Asteroide& asteroide) {
    //la colision ocurre si las coordenadas del proyectil coinciden con las del asteroide
    return (proyectil.x == asteroide.x && proyectil.y == asteroide.y);
}

void detectarColisionesProyectilAsteroides(Nave& nave, std::vector<Proyectil>& proyectiles, std::vector<Asteroide>& asteroides, std::vector<Asteroidec>& asteroidesc, std::vector<std::vector<char>>& pantalla) {
    for (Proyectil& proyectil : proyectiles) {
        for (Asteroide& asteroide : asteroides) {
            if (asteroide.activo && verificarColisionProyectilAsteroide(proyectil, asteroide)) {
                std::cout << "Colisión detectada entre un proyectil y un asteroide" << std::endl;
                                cout << "Colisión detectada entre un proyectil y un asteroide" << endl;

                // Incrementar los puntos del jugador
                nave.puntos += 100;

                // Desactivar el asteroide grande
                asteroide.activo = false;

                // Crear dos asteroides pequeños alrededor del asteroide destruido
                int x1 = asteroide.x - 1 >= 0 ? asteroide.x - 1 : pantalla[0].size() - 1;

                int y1 = asteroide.y - 1 >= 0 ? asteroide.y - 1 : pantalla.size() - 1;

                int x2 = asteroide.x + 1 < pantalla[0].size() ? asteroide.x + 1 : 0;
                int y2 = asteroide.y + 1 < pantalla.size() ? asteroide.y + 1 : 0;

                // Añadir los asteroides pequeños
                asteroidesc.emplace_back(x1, y1);  // Primer asteroide pequeño
                asteroidesc.emplace_back(x2, y2);  // Segundo asteroide pequeño

                // Terminar la detección de colisiones para este proyectil
                break;
            }
        }
    }
}




bool verificarColisionNaveAsteroidec(const Nave& nave, const Asteroidec& asteroidec) {
    //la colision ocurre si las coordenadas de la nave coinciden con las del asteroide
    return (nave.x == asteroidec.x && nave.y == asteroidec.y);
}

//Funcion que detecta colisiones entre la nave y todos los asteroides
void detectarColisionesNaveAsteroidesc(Nave& nave, vector<Asteroidec>& asteroidesc) {
    for (Asteroidec& asteroidec : asteroidesc) {
        if (asteroidec.activo && verificarColisionNaveAsteroidec(nave, asteroidec)) {
            cout << "Colision detectada entre la nave y un asteroide" << endl;
            
            // Restar una vida al jugador
            nave.vidas--;

            // Desactivar el asteroide (o realizar otra acción, como dividirlo si es grande)
            asteroidec.activo = false;

            //si pierde 
            if (nave.vidas <= 0) {
                nave.running = false; // Detener el juego si la nave se queda sin vidas
                cout << "Juego terminado, La nave ha sido destruida." << endl;
            }

            break;  // No es necesario seguir buscando otras colisiones en este ciclo
        }
    }
}


bool verificarColisionProyectilAsteroidec(const Proyectil& proyectil, const Asteroidec& asteroidec) {
    //la colision ocurre si las coordenadas del proyectil coinciden con las del asteroide
    return (proyectil.x == asteroidec.x && proyectil.y == asteroidec.y);
}


void detectarColisionesProyectilAsteroidesc(Nave& nave, std::vector<Proyectil>& proyectiles, std::vector<Asteroidec>& asteroidesc) {
    for (Proyectil& proyectil : proyectiles) {
        for (Asteroidec& asteroidec : asteroidesc) {
            if (asteroidec.activo && verificarColisionProyectilAsteroidec(proyectil, asteroidec)) {
                
                nave.puntos += 100;
                asteroidec.activo = false;
                break;
            }
            if (nave.puntos >= 600) {
                nave.running = false; // Detener el juego si la nave se queda sin vidas
                cout << "Juego terminado, La nave ha sido destruida." << endl;
            }
        }
    }
}
