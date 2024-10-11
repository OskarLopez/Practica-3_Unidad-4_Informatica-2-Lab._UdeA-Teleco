#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int MAX_USERS = 100; // Máximo número de usuarios
const int MAX_LENGTH = 50; // Longitud máxima de cédula y clave
const int COST_PER_ACCESS = 1000; // Costo por acceso

// Estructura para representar a un usuario
struct User {
    char cedula[MAX_LENGTH];
    char clave[MAX_LENGTH];
    int saldo;
};

// Función para encriptar la clave (invirtiendo los bits)
void encriptarClave(const char* clave, char* claveEncriptada) {
    int i = 0;
    while (clave[i] != '\0' && i < MAX_LENGTH) {
        claveEncriptada[i] = ~clave[i]; // Invertir bits
        i++;
    }
    claveEncriptada[i] = '\0'; // Terminar cadena
}

// Función para desencriptar la clave
void desencriptarClave(const char* claveEncriptada, char* claveDesencriptada) {
    int i = 0;
    while (claveEncriptada[i] != '\0' && i < MAX_LENGTH) {
        claveDesencriptada[i] = ~claveEncriptada[i]; // Invertir bits
        i++;
    }
    claveDesencriptada[i] = '\0'; // Terminar cadena
}

// Función para validar acceso del administrador
bool validarAccesoAdmin(const char* clave) {
    char claveEncriptada[MAX_LENGTH];
    encriptarClave(clave, claveEncriptada); // Encriptar la clave ingresada

    ifstream archivo("sudo.txt");
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo sudo.txt" << endl;
        return false;
    }

    char claveGuardada[MAX_LENGTH];
    archivo >> claveGuardada; // Leer clave encriptada desde el archivo
    archivo.close();

    // Comparar claves encriptadas
    return strcmp(claveEncriptada, claveGuardada) == 0; 
}

// Función para registrar un nuevo usuario
void registrarUsuario(User* usuarios, int& numUsuarios) {
    if (numUsuarios >= MAX_USERS) {
        cout << "No se pueden registrar más usuarios." << endl;
        return;
    }

    User nuevoUsuario;
    
    cout << "Ingrese cédula (máximo " << MAX_LENGTH - 1 << " caracteres): ";
    cin >> ws; // Eliminar espacios en blanco
    cin.getline(nuevoUsuario.cedula, MAX_LENGTH); // Leer cédula

    cout << "Ingrese clave (máximo " << MAX_LENGTH - 1 << " caracteres): ";
    cin.getline(nuevoUsuario.clave, MAX_LENGTH); // Leer clave

    // Encriptar la clave del nuevo usuario antes de guardarla
    char claveEncriptada[MAX_LENGTH];
    encriptarClave(nuevoUsuario.clave, claveEncriptada);
    strncpy(nuevoUsuario.clave, claveEncriptada, MAX_LENGTH - 1); // Guardar la clave encriptada
    nuevoUsuario.clave[MAX_LENGTH - 1] = '\0'; // Asegurarse de que la cadena esté terminada

    cout << "Ingrese saldo inicial: ";
    cin >> nuevoUsuario.saldo;

    // Validar que el saldo ingresado sea no negativo
    if (nuevoUsuario.saldo < 0) {
        cout << "El saldo no puede ser negativo." << endl;
        return;
    }

    usuarios[numUsuarios] = nuevoUsuario; // Agregar nuevo usuario
    numUsuarios++;
    cout << "Usuario registrado exitosamente." << endl;
}

// Función para acceder a un usuario
int accederUsuario(User* usuarios, int numUsuarios) {
    char cedula[MAX_LENGTH];
    char clave[MAX_LENGTH];

    cout << "Ingrese cédula: ";
    cin >> ws; // Eliminar espacios en blanco
    cin.getline(cedula, MAX_LENGTH); // Leer cédula

    cout << "Ingrese clave: ";
    cin.getline(clave, MAX_LENGTH); // Leer clave

    for (int i = 0; i < numUsuarios; i++) {
        if (strcmp(usuarios[i].cedula, cedula) == 0) {
            char claveDesencriptada[MAX_LENGTH];
            desencriptarClave(usuarios[i].clave, claveDesencriptada);
            if (strcmp(claveDesencriptada, clave) == 0) {
                return i; // Retornar índice del usuario
            }
        }
    }

    cout << "Cédula o clave incorrecta." << endl;
    return -1; // Usuario no encontrado
}

// Función para consultar saldo
void consultarSaldo(User& usuario) {
    // Actualiza el saldo del usuario al consultar
    usuario.saldo -= COST_PER_ACCESS; // Costo por acceso
    cout << "Saldo actual: " << usuario.saldo << " COP" << endl;
}

// Función para retirar dinero
void retirarDinero(User& usuario) {
    int cantidad;
    cout << "Ingrese cantidad a retirar: ";
    cin >> cantidad;

    // Validar fondos suficientes para la transacción
    if (cantidad <= usuario.saldo - COST_PER_ACCESS) {
        usuario.saldo -= (cantidad + COST_PER_ACCESS); // Costo por la transacción
        cout << "Retiro exitoso. Saldo restante: " << usuario.saldo << " COP" << endl;
    } else {
        cout << "Fondos insuficientes." << endl;
    }
}

// Función principal
int main() {
    User usuarios[MAX_USERS];
    int numUsuarios = 0;
    char claveAdmin[MAX_LENGTH];

    cout << "Ingrese la clave de administrador: ";
    cin >> ws; // Eliminar espacios en blanco
    cin.getline(claveAdmin, MAX_LENGTH); // Leer clave de administrador

    // Validar acceso como administrador
    if (!validarAccesoAdmin(claveAdmin)) {
        cout << "Acceso denegado." << endl;
        return 1;
    }

    int opcion;
    do {
        cout << "1. Registrar usuario" << endl;
        cout << "2. Acceder a usuario" << endl;
        cout << "3. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                registrarUsuario(usuarios, numUsuarios);
                break;
            case 2: {
                int index = accederUsuario(usuarios, numUsuarios);
                if (index != -1) {
                    int subOpcion;
                    do {
                        cout << "1. Consultar saldo" << endl;
                        cout << "2. Retirar dinero" << endl;
                        cout << "3. Salir" << endl;
                        cout << "Seleccione una opción: ";
                        cin >> subOpcion;

                        switch (subOpcion) {
                            case 1:
                                consultarSaldo(usuarios[index]);
                                break;
                            case 2:
                                retirarDinero(usuarios[index]);
                                break;
                        }
                    } while (subOpcion != 3);
                }
                break;
            }
            case 3:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opción no válida." << endl;
        }
    } while (opcion != 3);

    return 0;
}
