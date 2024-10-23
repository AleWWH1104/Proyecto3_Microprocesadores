#ifndef PROYECTIL_H
#define PROYECTIL_H

// Estructura que representa un proyectil en el juego
struct Proyectil {
    int x;               // Posición X del proyectil
    int y;               // Posición Y del proyectil
    bool activo;         // Estado del proyectil (activo o inactivo)
    int direccion;       // Dirección en la que se mueve el proyectil

    // Constructor para inicializar un proyectil
    Proyectil(int x, int y, int dir) : x(x), y(y), activo(true), direccion(dir) {}
};

#endif // PROYECTIL_H
