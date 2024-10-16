// Nave.cpp
#include "Nave.h"
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <termios.h>
#include <atomic>

using namespace std;  // Añadir aquí

// Constructor para Nave
Nave::Nave(int x, int y) : x(x), y(y), direccion(0), running(true) {}

int getch() {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    int ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

void moverNave(Nave& nave, char input) {
    switch (input) {
        case 'w': // Avanzar en la dirección actual
            switch (nave.direccion) {
                case 0: if (nave.y > 0) nave.y -= 1; break;
                case 1: if (nave.x < 39) nave.x += 1; break;
                case 2: if (nave.y < 19) nave.y += 1; break;
                case 3: if (nave.x > 0) nave.x -= 1; break;
            }
            break;
        case 'a': nave.direccion = (nave.direccion + 3) % 4; break; // Gira antihorario
        case 'd': nave.direccion = (nave.direccion + 1) % 4; break; // Gira horario
    }
}

void* ejecutarNave(void* arg) {
    Nave* nave = (Nave*)arg;

    while (nave->running) {
        char input = getch();    
        moverNave(*nave, input); 

        if (input == 'q') {
            nave->running = false;
        }

        usleep(50000);
    }

    return nullptr;
}

void dibujarPantallaNave(const Nave& nave, vector<vector<char>>& pantalla) {
    pantalla[nave.y][nave.x] = NAVE_ASCII[nave.direccion][0];
}
