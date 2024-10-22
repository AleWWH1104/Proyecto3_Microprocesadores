#ifndef PROYECTIL_H
#define PROYECTIL_H

struct Proyectil {
    int x, y;  // Posición del proyectil
    bool activo; // Estado del proyectil
    int direccion;

    Proyectil(int x, int y, int dir) : x(x), y(y), activo(true), direccion(dir) {}
};

#endif // PROYECTIL_H