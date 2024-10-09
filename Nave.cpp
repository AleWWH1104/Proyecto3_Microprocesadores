#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <termios.h>
#include <vector>
#include <atomic>

using namespace std;

//Representaciones ASCII 
const vector<string> NAVE_ASCII = {
    "▲",  
    "►", 
    "▼", 
    "◄" 
};

// Definir la estructura Nave
struct Nave {
    int x, y;    // Posición de la nave
    int direccion; 
    atomic<bool> running; // Variable para controlar el hilo

    // Constructor para inicializar la estructura con valores
    Nave(int posX, int posY, int dir)
        : x(posX), y(posY), direccion(dir), running(true) {}
};

// Función para obtener la entrada de teclado
int getch() {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // Desactivar el modo canónico y eco
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    int ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

void dibujarNave(const Nave& nave) {
    system("clear"); // Limpiar la pantalla
    cout << "\033[" << nave.y << ";" << nave.x << "H" << NAVE_ASCII[nave.direccion];  // Dibujar la nave
    cout.flush();
}

// Función para mover la nave según el input del usuario
void moverNave(Nave& nave, char input) {
    switch (input) {
        case 'w': // Avanzar en la dirección actual
            switch (nave.direccion) {
                case 0: nave.y -= 1; break;  // Mover hacia arriba
                case 1: nave.x += 1; break;  // Mover hacia la derecha
                case 2: nave.y += 1; break;  // Mover hacia abajo
                case 3: nave.x -= 1; break;  // Mover hacia la izquierda
            }
            break;
        case 'a': // Girar antihorario
            nave.direccion = (nave.direccion + 3) % 4; 
            break;
        case 'd': // Girar horario
            nave.direccion = (nave.direccion + 1) % 4;
            break;
    }
}

//Lo que hara el hilo de la nave
void* ejecutarNave(void* arg) {
    Nave* nave = (Nave*)arg;

    while (nave->running) {
        dibujarNave(*nave);
        char input = getch(); // Obtener entrada de teclado
        moverNave(*nave, input);
        if (input == 'q') { // Salir si se presiona 'q'
            nave->running = false;
        }
        usleep(50000); // Esperar un tiempo antes de redibujar
    }
    return nullptr;
}

int main() {
    // Inicializamos la estructura Nave
    Nave nave = {10, 10, 0};

    // Crear el hilo para la nave
    pthread_t hiloNave;
    pthread_create(&hiloNave, nullptr, ejecutarNave, &nave);

    // Esperar a que el hilo termine
    pthread_join(hiloNave, nullptr);

    return 0;
}