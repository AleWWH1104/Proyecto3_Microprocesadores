#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <termios.h>
#include <vector>
#include <atomic>

using namespace std;

// Definimos las representaciones ASCII de la nave en diferentes ángulos usando std::string
const vector<string> NAVE_ASCII = {"▲", "►", "▼", "◄"};

// Tamaño de la pantalla (matriz)
const int FILAS = 20;
const int COLUMNAS = 40;

// Definimos la estructura Nave, que contiene la información de la nave
struct Nave {
    int x, y;           // Posición de la nave
    int direccion;     
    atomic<bool> running; // Controla si el hilo sigue en ejecución
};

// Creamos la pantalla como una matriz
vector<vector<char>> pantalla(FILAS, vector<char>(COLUMNAS, ' '));

// Función para obtener la entrada de teclado sin esperar "Enter"
int getch() {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // Desactivar modo canónico y eco
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    int ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

// Función para dibujar la pantalla
void dibujarPantalla(const Nave& nave) {
    system("clear");  // Limpiar la pantalla

    // Dibujar la nave en la posición actual dentro de la matriz
    pantalla[nave.y][nave.x] = NAVE_ASCII[nave.direccion][0];  // Solo tomamos el primer carácter de la string

    // Mostrar la pantalla
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            cout << pantalla[i][j];
        }
        cout << endl;
    }

    // Limpiar la posición de la nave para la siguiente iteración
    pantalla[nave.y][nave.x] = ' ';
}

// Función para mover la nave según el input del usuario
void moverNave(Nave& nave, char input) {
    switch (input) {
        case 'w': // Avanzar en la dirección actual
            switch (nave.direccion) {
                case 0: // Mover hacia arriba
                    if (nave.y > 0) nave.y -= 1;
                    break;
                case 1: // Mover hacia la derecha
                    if (nave.x < COLUMNAS - 1) nave.x += 1;
                    break;
                case 2: // Mover hacia abajo
                    if (nave.y < FILAS - 1) nave.y += 1;
                    break;
                case 3: // Mover hacia la izquierda
                    if (nave.x > 0) nave.x -= 1;
                    break;
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

// Subrutina para ejecutar la lógica de la nave en el hilo
void* ejecutarNave(void* arg) {
    Nave* nave = (Nave*)arg;

    while (nave->running) {
        dibujarPantalla(*nave);  // Dibujar la nave y la pantalla
        char input = getch();    // Capturar entrada de teclado
        moverNave(*nave, input); // Mover la nave según la entrada

        // Detener si se presiona 'q'
        if (input == 'q') {
            nave->running = false;
        }

        usleep(50000);  // Esperar un tiempo antes de redibujar
    }

    return nullptr;
}

int main() {
    // Inicializamos la estructura Nave por partes
    Nave nave;
    nave.x = COLUMNAS / 2;   // Posicionar en el centro de la pantalla (eje x)
    nave.y = FILAS / 2;      // Posicionar en el centro de la pantalla (eje y)
    nave.direccion = 0;      // Dirección inicial (arriba)
    nave.running = true;     // Estado de ejecución

    // Crear el hilo para la nave
    pthread_t hiloNave;
    pthread_create(&hiloNave, nullptr, ejecutarNave, &nave);

    // Esperar a que el hilo termine
    pthread_join(hiloNave, nullptr);

    return 0;
}
