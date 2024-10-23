// Colision.cpp
#include "Colision.h"      // Incluir el encabezado para funciones y estructuras de colisión
#include "Nave.h"          // Incluir el encabezado para la estructura de la nave
#include "Asteroid.h"      // Incluir el encabezado para las estructuras de asteroides
#include <vector>          // Incluir la biblioteca de vectores
#include <iostream>        // Incluir la biblioteca de entrada/salida estándar

using namespace std;        // Usar el espacio de nombres estándar

// Declarar la pantalla global para la representación del juego
extern vector<vector<char>> pantalla;

// Función que genera un número aleatorio que puede ser -1 o 1
int randomSign() {
    // Generar un número aleatorio, 0 o 1
    int randomValue = rand() % 2;
    
    // Si es 0, devolver -1, si es 1, devolver 1
    return (randomValue == 0) ? -1 : 1;
}

// Función que verifica si la nave y un asteroide han colisionado
bool verificarColisionNaveAsteroide(const Nave& nave, const Asteroide& asteroide) {
    // La colisión ocurre si las coordenadas de la nave coinciden con las del asteroide
    return (nave.x == asteroide.x && nave.y == asteroide.y);
}

// Función que detecta colisiones entre la nave y todos los asteroides
void detectarColisionesNaveAsteroides(Nave& nave, vector<Asteroide>& asteroides) {
    for (Asteroide& asteroide : asteroides) {
        // Verificar si el asteroide está activo y si hay colisión con la nave
        if (asteroide.activo && verificarColisionNaveAsteroide(nave, asteroide)) {
            cout << "Colision detectada entre la nave y un asteroide" << endl;
            
            // Restar una vida al jugador
            nave.vidas--;

            // Desactivar el asteroide (o realizar otra acción, como dividirlo si es grande)
            asteroide.activo = false;

            // Si el jugador pierde todas las vidas
            if (nave.vidas <= 0) {
                nave.running = false; // Detener el juego si la nave se queda sin vidas
                cout << "Juego terminado, La nave ha sido destruida." << endl;
            }

            break;  // No es necesario seguir buscando otras colisiones en este ciclo
        }
    }
}

// Función que verifica si un proyectil ha colisionado con un asteroide
bool verificarColisionProyectilAsteroide(const Proyectil& proyectil, const Asteroide& asteroide) {
    // La colisión ocurre si las coordenadas del proyectil coinciden con las del asteroide
    return (proyectil.x == asteroide.x && proyectil.y == asteroide.y);
}

// Función que detecta colisiones entre los proyectiles y todos los asteroides
void detectarColisionesProyectilAsteroides(Nave& nave, std::vector<Proyectil>& proyectiles, std::vector<Asteroide>& asteroides, std::vector<Asteroidec>& asteroidesc, std::vector<std::vector<char>>& pantalla) {
    for (Proyectil& proyectil : proyectiles) {
        for (Asteroide& asteroide : asteroides) {
            // Verificar si el asteroide está activo y si hay colisión con el proyectil
            if (asteroide.activo && verificarColisionProyectilAsteroide(proyectil, asteroide)) {
                std::cout << "Colisión detectada entre un proyectil y un asteroide" << std::endl;

                // Incrementar los puntos del jugador
                nave.puntos += 100;

                // Desactivar el asteroide grande
                asteroide.activo = false;

                // Crear dos asteroides pequeños alrededor del asteroide destruido
                int x1 = asteroide.x - 1 >= 0 ? asteroide.x - 1 : pantalla[0].size() - 1;
                int y1 = asteroide.y - 1 >= 0 ? asteroide.y - 1 : pantalla.size() - 1;
                int x2 = asteroide.x + 1 < pantalla[0].size() ? asteroide.x + 1 : 0;
                int y2 = asteroide.y + 1 < pantalla.size() ? asteroide.y + 1 : 0;

                // Añadir los asteroides pequeños a la lista
                asteroidesc.emplace_back(x1, y1);  // Primer asteroide pequeño
                asteroidesc.emplace_back(x2, y2);  // Segundo asteroide pequeño

                // Terminar la detección de colisiones para este proyectil
                break;
            }
        }
    }
}

// Función que verifica si la nave y un asteroide pequeño han colisionado
bool verificarColisionNaveAsteroidec(const Nave& nave, const Asteroidec& asteroidec) {
    // La colisión ocurre si las coordenadas de la nave coinciden con las del asteroide pequeño
    return (nave.x == asteroidec.x && nave.y == asteroidec.y);
}

// Función que detecta colisiones entre la nave y todos los asteroides pequeños
void detectarColisionesNaveAsteroidesc(Nave& nave, vector<Asteroidec>& asteroidesc) {
    for (Asteroidec& asteroidec : asteroidesc) {
        // Verificar si el asteroide pequeño está activo y si hay colisión con la nave
        if (asteroidec.activo && verificarColisionNaveAsteroidec(nave, asteroidec)) {
            cout << "Colisión detectada entre la nave y un asteroide pequeño" << endl;
            
            // Restar una vida al jugador
            if (nave.running){
                nave.vidas--;
            }

            // Desactivar el asteroide pequeño
            asteroidec.activo = false;

            // Si el jugador pierde todas las vidas
            if (nave.vidas <= 0) {
                nave.running = false; // Detener el juego si la nave se queda sin vidas
                cout << "Juego terminado, La nave ha sido destruida." << endl;
            }

            break;  // No es necesario seguir buscando otras colisiones en este ciclo
        }
    }
}

// Función que verifica si un proyectil ha colisionado con un asteroide pequeño
bool verificarColisionProyectilAsteroidec(const Proyectil& proyectil, const Asteroidec& asteroidec) {
    // La colisión ocurre si las coordenadas del proyectil coinciden con las del asteroide pequeño
    return (proyectil.x == asteroidec.x && proyectil.y == asteroidec.y);
}

// Función que detecta colisiones entre los proyectiles y todos los asteroides pequeños
void detectarColisionesProyectilAsteroidesc(Nave& nave, std::vector<Proyectil>& proyectiles, std::vector<Asteroidec>& asteroidesc) {
    for (Proyectil& proyectil : proyectiles) {
        for (Asteroidec& asteroidec : asteroidesc) {
            // Verificar si el asteroide pequeño está activo y si hay colisión con el proyectil
            if (asteroidec.activo && verificarColisionProyectilAsteroidec(proyectil, asteroidec)) {
                // Incrementar los puntos del jugador
                nave.puntos += 50;

                // Desactivar el asteroide pequeño
                asteroidec.activo = false;
                break; // Terminar la detección de colisiones para este proyectil
            }

            // Si el jugador alcanza un puntaje de 600, se termina el juego
            if (nave.puntos >= 600) {
                nave.running = false; // Detener el juego si el jugador alcanza el puntaje máximo
                cout << "Juego terminado, La nave ha sido destruida." << endl;
            }
        }
    }
}
