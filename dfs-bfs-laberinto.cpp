#include <iostream>  // Para entrada y salida (cout, cin)
#include <vector>    // Para usar matrices dinámicas (vectores de vectores)
#include <stack>     // Para el algoritmo de generación (DFS)
#include <queue>     // Para el algoritmo de resolución (BFS)
#include <cstdlib>   // Para funciones generales como atoi()
#include <ctime>     // Para medir el tiempo de ejecución y clock()
#include <algorithm> // Para usar la función shuffle()
#include <random>    // Para generar números aleatorios de alta calidad

// Si estamos en Windows, incluimos la librería necesaria para configurar la terminal
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// Estructura para guardar coordenadas X e Y de forma agrupada
struct Pos {
    int x, y;
};

// Variables globales para las dimensiones y el mapa del laberinto
int N, M;
vector<vector<char>> lab;

// Función para verificar que una celda esté dentro de los límites de la matriz
bool esValido(int x, int y) {
    return x >= 0 && y >= 0 && x < N && y < M;
}

/*
    LABERINTO (DFS - Depth First Search)

 */
void generarLaberinto() {
    // Llenamos la matriz con muros '#' inicialmente
    lab.assign(N, vector<char>(M, '#'));
    vector<vector<bool>> visitado(N, vector<bool>(M, false));
    stack<Pos> pila; // Pila para el Backtracking (volver atrás cuando nos encerramos)
    
    // Punto de partida: Entrada (0,0)
    pila.push({0, 0});
    visitado[0][0] = true;
    lab[0][0] = 'S'; // Marcamos la entrada START

    // Movimientos de 2 en 2 para saltar muros y crear pasillos divisorios
    int dx[] = {0, 0, 2, -2};
    int dy[] = {2, -2, 0, 0};

    // Generador de números aleatorios moderno
    random_device rd;
    mt19937 g(rd());

    while (!pila.empty()) {
        Pos actual = pila.top();
        vector<int> dirs = {0, 1, 2, 3}; // Direcciones: Arriba, Abajo, Izquierda, Derecha
        shuffle(dirs.begin(), dirs.end(), g); // Mezclamos las direcciones aleatoriamente

        bool movio = false;
        for (int d : dirs) {
            int nx = actual.x + dx[d];
            int ny = actual.y + dy[d];

            // Si la celda a 2 pasos es válida y no se visitó...
            if (esValido(nx, ny) && !visitado[nx][ny]) {
                // Rompemos el muro intermedio (a 1 paso de distancia)
                lab[actual.x + dx[d] / 2][actual.y + dy[d] / 2] = ' ';
                // Marcamos la celda destino como pasillo
                lab[nx][ny] = ' ';
                visitado[nx][ny] = true;
                pila.push({nx, ny}); // Avanzamos a la nueva celda
                movio = true;
                break;
            }
        }
        // Si no hay salida en ninguna dirección, retrocedemos (pop)
        if (!movio) pila.pop();
    }

    // Salida garantizada en la esquina inferior derecha
    lab[N - 1][M - 1] = 'E';
    // Si la salida quedó rodeada de muros, abrimos una conexión forzada
    if (lab[N - 2][M - 1] == '#' && lab[N - 1][M - 2] == '#') {
        lab[N - 2][M - 1] = ' '; 
    }
}

/**
 * RESOLUCIÓN DEL LABERINTO (BFS - Breadth First Search)
 * Usamos BFS porque garantiza encontrar el CAMINO MÁS CORTO.
 */
void resolverLaberinto() {
    queue<Pos> q; // Cola para explorar nivel por nivel
    
    // Matriz para guardar de qué celda venimos (sirve para reconstruir el camino)
    vector<vector<Pos>> padre(N, vector<Pos>(M));
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            padre[i][j] = {-1, -1};
        }
    }

    vector<vector<bool>> vis(N, vector<bool>(M, false));

    q.push({0, 0});
    vis[0][0] = true;

    // Movimientos de 1 en 1 para explorar pasillos
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    bool encontrado = false;
    while (!q.empty()) {
        Pos actual = q.front();
        q.pop();

        // Si llegamos a la salida 'E', terminamos
        if (actual.x == N - 1 && actual.y == M - 1) {
            encontrado = true;
            break;
        }

        for (int i = 0; i < 4; i++) {
            int nx = actual.x + dx[i];
            int ny = actual.y + dy[i];

            // Solo pasamos por espacios vacíos y no visitados
            if (esValido(nx, ny) && !vis[nx][ny] && lab[nx][ny] != '#') {
                vis[nx][ny] = true;
                padre[nx][ny] = actual; // Guardamos la referencia del "padre"
                q.push({nx, ny});
            }
        }
    }

    // Reconstrucción del camino usando los asteriscos '*'
    if (encontrado) {
        Pos paso = padre[N - 1][M - 1];
        while (!(paso.x == 0 && paso.y == 0)) {
            if (lab[paso.x][paso.y] == ' ') lab[paso.x][paso.y] = '*';
            paso = padre[paso.x][paso.y]; // Vamos hacia atrás
        }
    }
    lab[0][0] = 'S';
    lab[N - 1][M - 1] = 'E';
}

void imprimir() {
    cout << "\n--- LABERINTO COMPLETO ---\n" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (lab[i][j] == '#') cout << "##";      // Muro sólido (doble para estética)
            else if (lab[i][j] == '*') cout << " ."; // Camino de salida
            else if (lab[i][j] == ' ') cout << "  "; // Pasillo vacío
            else cout << " " << lab[i][j];          // Caracteres S y E
        }
        cout << endl;
    }
}

int main(int argc, char* argv[]) {
    // Configuración para que Windows soporte caracteres especiales
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    // Si pasamos argumentos (ej: ./laberinto 15 15), los tomamos
    if (argc == 3) {
        N = atoi(argv[1]);
        M = atoi(argv[2]);
        //#include <cstdlib>
    } else {
        N = 21; M = 21; // Tamaño base
    }

    // El algoritmo requiere dimensiones impares para que el perímetro sea cerrado
    if (N % 2 == 0) N++;
    if (M % 2 == 0) M++;

    clock_t inicio = clock(); // Inicia el cronómetro
    
    generarLaberinto();
    resolverLaberinto();
    
    clock_t fin = clock(); // Termina el cronómetro

    imprimir();

    // Cálculo del tiempo transcurrido
    double tiempo = double(fin - inicio) / CLOCKS_PER_SEC;
    cout << "\nProcesado en: " << tiempo << " segundos." << endl;

    return 0;
}