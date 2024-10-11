#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Función para invertir bits en un string
void invertirBits(string &bloque) {
    for (size_t i = 0; i < bloque.size(); i++) {
        bloque[i] = (bloque[i] == '1') ? '0' : '1';
    }
}

// Función que realiza el primer método de decodificación
string decodificarMetodo1(const string &binarioCodificado, int n) {
    string binarioDecodificado = "";
    int longitud = binarioCodificado.size();

    for (int i = 0; i < longitud; i += n) {
        string bloque = binarioCodificado.substr(i, n);  // Extraemos el bloque de n bits

        // Si es el primer bloque, invertimos todos los bits
        if (i == 0) {
            invertirBits(bloque);
        } else {
            // Contamos los 1s y 0s en el bloque anterior
            string bloqueAnterior = binarioCodificado.substr(i - n, n);
            int unos = 0, ceros = 0;
            for (char bit : bloqueAnterior) {
                if (bit == '1') unos++;
                else ceros++;
            }

            // Aplicar reglas de inversión basadas en el bloque anterior
            if (unos == ceros) {
                invertirBits(bloque);  // Invertir todos los bits
            } else if (ceros > unos) {
                for (size_t j = 0; j < bloque.size(); j += 2) {
                    if (j < bloque.size()) {
                        bloque[j] = (bloque[j] == '1') ? '0' : '1';  // Invertir cada 2 bits
                    }
                }
            } else {
                for (size_t j = 0; j < bloque.size(); j += 3) {
                    if (j < bloque.size()) {
                        bloque[j] = (bloque[j] == '1') ? '0' : '1';  // Invertir cada 3 bits
                    }
                }
            }
        }

        binarioDecodificado += bloque;  // Añadir el bloque decodificado al resultado final
    }

    return binarioDecodificado;
}

// Función que realiza el segundo método de decodificación
string decodificarMetodo2(const string &binarioCodificado, int n) {
    string binarioDecodificado = "";
    int longitud = binarioCodificado.size();

    for (int i = 0; i < longitud; i += n) {
        string bloque = binarioCodificado.substr(i, n);  // Extraemos el bloque de n bits
        string bloqueDecodificado(n, '0');  // Crear un string temporal para almacenar el bloque decodificado

        // Desplazar los bits en el orden inverso del codificado
        for (size_t j = 0; j < bloque.size(); j++) {
            bloqueDecodificado[(j + 1) % bloque.size()] = bloque[j];  // Desplazar los bits
        }

        binarioDecodificado += bloqueDecodificado;  // Añadir el bloque decodificado
    }

    return binarioDecodificado;
}

// Función que convierte una cadena binaria a un carácter
char convertirBinarioAChar(const string &binario) {
    char valor = 0;
    for (size_t i = 0; i < 8; i++) {
        valor = valor * 2 + (binario[i] - '0');
    }
    return valor;
}

// Función principal
int main() {
    int n, metodo;
    string archivoEntrada, nombreArchivoSalida; // Cambiamos el nombre de la variable

    // Ingresar la semilla y método
    cout << "Ingresa la semilla (n) para dividir los bloques: ";
    cin >> n;

    cout << "Selecciona el método de decodificación (1 o 2): ";
    cin >> metodo;

    // Pedimos el nombre del archivo de entrada
    cout << "Ingresa el nombre del archivo binario codificado: ";
    cin >> archivoEntrada;

    // Pedimos el nombre del archivo de salida
    cout << "Ingresa el nombre del archivo de salida de texto: ";
    cin >> nombreArchivoSalida; // Usamos el nuevo nombre

    // Leemos el archivo binario
    ifstream archivo(archivoEntrada, ios::binary);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo fuente." << endl;
        return 1;
    }

    // Convertir el contenido del archivo a binario
    string binarioCodificado = "";
    char byte;
    while (archivo.read(&byte, sizeof(char))) {
        for (int i = 7; i >= 0; i--) {
            binarioCodificado += ((byte >> i) & 1) ? '1' : '0';
        }
    }
    archivo.close();

    cout << "Archivo codificado en binario: " << binarioCodificado << endl;

    // Decodificar el archivo en binario según el método seleccionado
    string binarioDecodificado;
    if (metodo == 1) {
        binarioDecodificado = decodificarMetodo1(binarioCodificado, n);
    } else if (metodo == 2) {
        binarioDecodificado = decodificarMetodo2(binarioCodificado, n);
    } else {
        cout << "Método de decodificación no válido." << endl;
        return 1;
    }

    // Generar el archivo de salida
    ofstream archivoSalida(nombreArchivoSalida); // Usamos el nuevo nombre
    if (!archivoSalida.is_open()) {
        cout << "Error al abrir el archivo de salida." << endl;
        return 1;
    }

    // Convertir el binario decodificado a caracteres
    for (size_t i = 0; i < binarioDecodificado.size(); i += 8) {
        string bloque = binarioDecodificado.substr(i, 8);
        if (bloque.size() < 8) {
            // Si el bloque no tiene 8 bits, completamos con ceros
            bloque.append(8 - bloque.size(), '0');
        }
        char caracter = convertirBinarioAChar(bloque);
        archivoSalida << caracter;  // Guardar el caracter en el archivo
    }

    archivoSalida.close();

    cout << "Archivo decodificado generado exitosamente en: " << nombreArchivoSalida << endl;

    return 0;
}
