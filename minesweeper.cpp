#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <chrono>

using namespace std;

#define MAX_CASILLAS 8
#define MAX_BOMBAS 10

void crearTableroVisual(char **);
void mostrarTableroVisual(char **);
void crearTableroLogico(char **);
void colocarBombas(char **);
void colocarPistas(char **, char **);
void mostrarTableroLogico(char **);
void juegoPrincipal();
bool bombaEncontrada(int, int, char **, char **);
void revelarCasillaActual(int, int, char **, char **, int *);
void revelarBombas(char **, char **);
void revelarCasillasRestantes(int, int, char **, char **, int *);
bool ciclarMarcado(int, int, char **, int *);
void liberarMemoria(char **, char **);


int main(void) {
    srand(time(nullptr));

    juegoPrincipal();
    return 0;
}


void crearTableroVisual(char **tableroVisual) {
    // Asigna en cada casilla de vector principal un vector (Arreglo de arreglos)
    for (int i = 0; i < MAX_CASILLAS + 1; i++) {
        tableroVisual[i] = new char[MAX_CASILLAS + 1];
    }

    // Inicializa el tablero de #
    for (int i = 0; i < MAX_CASILLAS + 1; i++) {
        for (int j = 0; j < MAX_CASILLAS + 1; j++) {
            if (i == 0 && j == 0) {
                tableroVisual[i][j] = ' ';
            } else if (i == 0) {
                tableroVisual[i][j] = '1' + (j - 1);
            } else if (j == 0) {
                tableroVisual[i][j] = '1' + (i - 1);
            }    
            else {
                tableroVisual[i][j] = '#';
            }
        }
        
    }
}

void mostrarTableroVisual(char **tableroVisual) {
   cout << "\n=======      TABLERO      =======\n" << endl;
    // Recorre cada vector para mostrar su contenido
   for (int i = 0; i < MAX_CASILLAS + 1; i++) {
        for (int j = 0; j < MAX_CASILLAS + 1; j++) {
            cout << tableroVisual[i][j] << "   ";
        }
        cout << endl << endl;
    }
    cout << endl;
    
}

// Asigna en cada casilla de vector principal un vector (Arreglo de arreglos)
void crearTableroLogico(char **tableroLogico) {
    for (int i = 0; i < MAX_CASILLAS; i++) {
        tableroLogico[i] = new char[MAX_CASILLAS];
    }
    
    // Inicializa el tablero de #
    for (int i = 0; i < MAX_CASILLAS; i++) {
        for (int j = 0; j < MAX_CASILLAS; j++) {
           tableroLogico[i][j] = '#';
        }
        
    }

    colocarBombas(tableroLogico);
}

void colocarBombas(char **tableroLogico) {
    int bombas = 0;

    while (bombas < MAX_BOMBAS) {
        int filasRandom = rand() % MAX_CASILLAS;
        int columnasRandom = rand() % MAX_CASILLAS;

        if (tableroLogico[filasRandom][columnasRandom] != 'B') {
            tableroLogico[filasRandom][columnasRandom] = 'B';
            bombas++;
        } 
    }
}


void mostrarTableroLogico(char **tableroLogico) {
   cout << endl;
    // Recorre cada vector para mostrar su contenido
   for (int i = 0; i < MAX_CASILLAS; i++) {
       for (int j = 0; j < MAX_CASILLAS; j++) {
       cout << tableroLogico[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

void colocarPistas(char **tableroVisual, char **tableroLogico) {
    for (int i = 0; i < MAX_CASILLAS; i++) {
        for (int j = 0; j < MAX_CASILLAS; j++) {
            if (tableroLogico[i][j] != 'B') {
                int contadorBombas = 0;
                if (i >= 1 && tableroLogico[i - 1][j] == 'B') {
                    contadorBombas++;
                }
                    
                if (i < MAX_CASILLAS - 1 && tableroLogico[i + 1][j] == 'B') {   
                    contadorBombas++;
                }
                    
                if (j >= 1 && tableroLogico[i][j - 1] == 'B') {
                    contadorBombas++;
                }

                if (j < MAX_CASILLAS - 1 && tableroLogico[i][j + 1] == 'B') {
                    contadorBombas++;
                }

                if (i >= 1 && j < MAX_CASILLAS - 1 && tableroLogico[i - 1][j + 1] == 'B') {
                    contadorBombas++;
                }

                if (i < MAX_CASILLAS - 1 && j >= 1 && tableroLogico[i + 1][j - 1] == 'B') {
                    contadorBombas++;
                }

                if (i >= 1 && j >= 1 && tableroLogico[i - 1][j - 1] == 'B') {
                    contadorBombas++;
                }
                    
                if (i < MAX_CASILLAS - 1 && j < MAX_CASILLAS - 1 && tableroLogico[i + 1][j + 1] == 'B') {
                    contadorBombas++;
                }

                if (contadorBombas > 0) {
                    tableroLogico[i][j] = contadorBombas + '0';
                } else {
                    tableroLogico[i][j] = '-';
                }
                
            }
        }
    }
}

void juegoPrincipal() {
    int playAgain = 1;

    while (playAgain == 1) {
        char **tableroVisual = new char*[MAX_CASILLAS + 1];
        char **tableroLogico = new char*[MAX_CASILLAS];

        crearTableroVisual(tableroVisual);
        crearTableroLogico(tableroLogico);
        colocarPistas(tableroVisual, tableroLogico);
        bool end = false;
        bool exit = false;
        int casillasRestantes = MAX_CASILLAS * MAX_CASILLAS - MAX_BOMBAS;
        auto startTime = chrono::steady_clock::now();
        int banderasRestantes = MAX_BOMBAS;

        while (casillasRestantes > 0 && !end && !exit) {
            auto currentTime = chrono::steady_clock::now();  
            long long diff = chrono::duration_cast<chrono::seconds>(currentTime - startTime).count();
            int opc = -1;
            bool val = true;
            do {
                mostrarTableroVisual(tableroVisual);
                //mostrarTableroLogico(tableroLogico);
                cout << "-- Casillas Seguras Restantes: " << casillasRestantes << " ---" << "\nTiempo: " << diff << " segundos" << "\t Banderas Restantes: " << banderasRestantes << endl;
                cout << "\n1) Revelar Casilla\n2) Marcar Casilla (Bandera / Interrogacion)\n3) Terminar juego" << endl;
                cin >> opc;

                if (cin.fail()) {
                    cout << "\nError: Solo se permite valores numericos. Intente de nuevo: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                } 
                
                int x = -1;
                int y = -1;
        
                bool exito = false;
                
                switch (opc) {
                    case 1:
                        cout << "Ingrese las coordenadas de la casilla a escoger (x, y) respectivamente (Ej. 5 1): ";
                        do {
                            cin >> x >> y;

                            if (cin.fail()) {
                                cout << "Error: Solo se permite valores numericos. Intente de nuevo: ";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            } 
                            else if (x < 1 || x > MAX_CASILLAS || y < 1 || y > MAX_CASILLAS) {
                                cout << "Error: Casilla fuera de rango. Intente de nuevo: ";
                                continue;
                            }     
                        } while (cin.fail() || x < 1 || x > MAX_CASILLAS || y < 1 || y > MAX_CASILLAS);   
                        
                        if (tableroVisual[x][y] == 'P') {
                            cout << "\nNo puedes revelar una casilla con bandera." << endl;
                            val = false;
                            break;
                        }

                        if (tableroVisual[x][y] != '#' && tableroVisual[x][y] != '?') {
                            cout << "\nEsta casilla ya ha sido revelada. Intente con otra." << endl;
                            val = false;
                            break;
                        }

                        if (bombaEncontrada(x - 1, y - 1, tableroVisual, tableroLogico)) {
                            revelarBombas(tableroVisual, tableroLogico);
                            mostrarTableroVisual(tableroVisual);
                            cout << "\nTiempo: " << diff << " segundos" << "\t Banderas Restantes: " << banderasRestantes << endl;
                            val = true;
                            end = true;
                        }

                        if (tableroLogico[x - 1][y - 1] == '-') {
                            revelarCasillasRestantes(x - 1, y - 1, tableroVisual, tableroLogico, &casillasRestantes);
                        } else {
                            revelarCasillaActual(x - 1, y - 1, tableroVisual, tableroLogico, &casillasRestantes);
                        }

                
                        break;
                    case 2: 
                        cout << "Ingrese las coordenadas de la casilla a poner la bandera (x, y) respectivamente (Ej. 3 2): ";
                        do {
                            cin >> x >> y;
                            
                            if (cin.fail()) {
                                cout << "Error: Solo se permite valores numericos. Intente de nuevo: ";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            } 
                            else if (x < 1 || x > MAX_CASILLAS || y < 1 || y > MAX_CASILLAS) {
                                cout << "Error: Casilla fuera de rango. Intente de nuevo: ";
                                continue;
                            } 

                            exito = ciclarMarcado(x, y, tableroVisual, &banderasRestantes);

                            if (!exito) {
                                cout << "Error: Casilla invalida u ocupada. Intente de nuevo: ";
                                continue;
                            }

                        } while (cin.fail() || x < 1 || x > MAX_CASILLAS || y < 1 || y > MAX_CASILLAS || !exito);
                        val = true;
                        break;
                    case 3:
                        exit = true;
                        break;
                    default:
                        val = false;
                        break;
                }
            } while (cin.fail() || !val);   
        }

        if (!exit) {
            if (casillasRestantes > 0) {
                cout << "\nPerdiste" << endl;
            } else {
                cout << "\nGanaste" << endl;
            } 
        } else {
            cout << "\nBien jugado!" << endl;
        }


        cout << "Desea jugar de nuevo 1. Si / 2. No?: " << endl;
        bool opcVal = false;
        do {
            cin >> playAgain;

            if (cin.fail()) {
                cout << "Error: Solo se permite valores numericos. Intente de nuevo: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else if (playAgain != 1 && playAgain != 2) {
                cout << "Error: Opcion invalida. Ingrese 1 para Si o 2 para No: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                opcVal = true;
            }
        } while (!opcVal);

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (playAgain == 2) {
            liberarMemoria(tableroVisual, tableroLogico);
            break;
        }

        liberarMemoria(tableroVisual, tableroLogico);
    }

    cout << "\nHasta luego!" << endl;    
}

bool bombaEncontrada(int x, int y, char **tableroVisual, char **tableroLogico) {
    if (tableroLogico[x][y] == 'B' && tableroVisual[x + 1][y + 1] != 'P') {
        return true;
    }

    return false;
} 

void revelarCasillaActual(int x, int y, char **tableroVisual, char **tableroLogico, int *casillasRestantes) {
    if (tableroVisual[x + 1][y + 1] != '?' && tableroVisual[x + 1][y + 1] != '#') {
        return;
    } 
    
    tableroVisual[x + 1][y + 1] = tableroLogico[x][y];
    (*casillasRestantes)--;
}


void revelarBombas(char **tableroVisual, char **tableroLogico) {
    for (int i = 0; i < MAX_CASILLAS; i++) {
        for (int j = 0; j < MAX_CASILLAS; j++) {
            if (tableroVisual[i + 1][j + 1] == 'P' && tableroLogico[i][j] == 'B') {
                continue;
            } else if (tableroLogico[i][j] == 'B') {
                tableroVisual[i + 1][j + 1] = 'B';
            } else if (tableroVisual[i + 1][j + 1] == 'P' && tableroLogico[i][j] != 'B') {
                tableroVisual[i + 1][j + 1] = 'X';
            }
        }
    }
}

void revelarCasillasRestantes(int x, int y, char **tableroVisual, char **tableroLogico, int *casillasRestantes) {
    if (x < 0 || x >= MAX_CASILLAS || y < 0 || y >= MAX_CASILLAS) {
        return;
    }

    if (tableroVisual[x + 1][y + 1] != '?' && tableroVisual[x + 1][y + 1] != '#') {
        return;
    } 

    if (tableroLogico[x][y] == 'B') {
        return;
    }

    if (tableroLogico[x][y] >= '1' && tableroLogico[x][y] <= '8') {
        tableroVisual[x + 1][y + 1] = tableroLogico[x][y];
        (*casillasRestantes)--;
        return;
    }

    tableroVisual[x + 1][y + 1] = tableroLogico[x][y];
    (*casillasRestantes)--;

     if (x >= 1) {
        revelarCasillasRestantes(x - 1, y, tableroVisual, tableroLogico, casillasRestantes);
    }
                    
    if (x < MAX_CASILLAS - 1) {   
        revelarCasillasRestantes(x + 1, y, tableroVisual, tableroLogico, casillasRestantes);
    }
                    
    if (y >= 1) {
        revelarCasillasRestantes(x, y - 1, tableroVisual, tableroLogico, casillasRestantes);
    }

    if (y < MAX_CASILLAS - 1) {
        revelarCasillasRestantes(x, y + 1, tableroVisual, tableroLogico, casillasRestantes);
    }

    if (x >= 1 && y < MAX_CASILLAS - 1) {
        revelarCasillasRestantes(x - 1, y + 1, tableroVisual, tableroLogico, casillasRestantes);
    }

    if (x < MAX_CASILLAS - 1 && y >= 1) {
        revelarCasillasRestantes(x + 1, y - 1, tableroVisual, tableroLogico, casillasRestantes);
    }

    if (x >= 1 && y >= 1) {
        revelarCasillasRestantes(x - 1, y - 1, tableroVisual, tableroLogico, casillasRestantes);
    }
                    
    if (x < MAX_CASILLAS - 1 && y < MAX_CASILLAS - 1) {
        revelarCasillasRestantes(x + 1, y + 1, tableroVisual, tableroLogico, casillasRestantes);
    }
}

bool ciclarMarcado(int x, int y, char **tableroVisual, int *banderasRestantes) {
    if (tableroVisual[x][y] != '#' && tableroVisual[x][y] != 'P' && tableroVisual[x][y] != '?') {
        return false;
    }

    if (tableroVisual[x][y] == '#') {
        tableroVisual[x][y] = 'P';
        (*banderasRestantes)--;
    } 
    else if (tableroVisual[x][y] == 'P') {
        tableroVisual[x][y] = '?';
        (*banderasRestantes)++;
    } else {
        tableroVisual[x][y] = '#';
    }
    

    
    return true;
}

void liberarMemoria(char **tableroVisual, char **tableroLogico) {
    for (int i = 0; i < MAX_CASILLAS; i++) {
        delete[] tableroLogico[i];
    }

    for (int i = 0; i < MAX_CASILLAS + 1; i++) {
        delete[] tableroVisual[i];
    }

    delete[] tableroVisual;
    delete[] tableroLogico;
}