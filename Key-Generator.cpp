#include <iostream>
#include <fstream>

using namespace std;

// Función para encriptar la clave (invirtiendo los bits)
void encriptarClave(const char* clave, char* claveEncriptada) {
    int i = 0;
    while (clave[i] != '\0' && i < 50) { // Asegúrate de no exceder el límite
        claveEncriptada[i] = ~clave[i]; // Invertir bits
        i++;
    }
    claveEncriptada[i] = '\0'; // Terminar cadena
}

// Función para guardar la clave encriptada en un archivo
void guardarEnArchivo(const char* nombreArchivo, const char* claveEncriptada) {
    ofstream archivo(nombreArchivo, ios::binary); // Abrir archivo en modo binario
    if (archivo.is_open()) {
        archivo << claveEncriptada; // Guardar la clave encriptada
        archivo.close();
        cout << "Clave encriptada guardada en " << nombreArchivo << endl;
    } else {
        cerr << "Error al abrir el archivo para escribir." << endl;
    }
}

int main() {
    const int MAX_CLAVE = 50; // Tamaño máximo de la clave
    char clave[MAX_CLAVE];
    char claveEncriptada[MAX_CLAVE]; // 50 bytes + terminador

    cout << "Ingrese la clave a encriptar: ";
    cin.getline(clave, MAX_CLAVE); // Leer clave del usuario

    encriptarClave(clave, claveEncriptada); // Encriptar la clave
    guardarEnArchivo("sudo.txt", claveEncriptada); // Guardar en el archivo

    return 0;
}
