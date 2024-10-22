#ifndef PROYECTIL_H
#define PROYECTIL_H

struct Proyectil {
    int x, y;
    bool activo;
    int direccion;

    Proyectil(int x, int y, int dir) : x(x), y(y), activo(true), direccion(dir) {}
};

#endif // PROYECTIL_H
