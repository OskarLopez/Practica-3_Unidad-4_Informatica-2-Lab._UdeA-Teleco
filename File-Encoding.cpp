#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Función para convertir un carácter a su representación binaria de 8 bits
void convertirCaracterABinario(char c, string &binario) {
    for (int i = 7; i >= 0; i--) {
        binario += ((c >> i) & 1) ? '1' : '0';
    }
}

// Función para invertir bits en un string
void invertirBits(string &bloque, int regla) {
    for (size_t i = 0; i < bloque.size(); i++) {
        if (regla == 1) {
            bloque[i] = (bloque[i] == '1') ? '0' : '1';
        } else if (regla == 2 && i % 2 == 0) {
            bloque[i] = (bloque[i] == '1') ? '0' : '1';
        } else if (regla == 3 && i % 3 == 0) {
            bloque[i] = (bloque[i] == '1') ? '0' : '1';
        }
    }
}

// Función para contar 1s y 0s en un string de bits
void contarBits(const string &bloque, int &unos, int &ceros) {
    unos = 0;
    ceros = 0;
    for (char bit : bloque) {
        if (bit == '1') unos++;
        else ceros++;
    }
}

// Función que realiza el primer método de codificación
string codificarMetodo1(const string &binario, int n) {
    string binarioCodificado = "";
    int longitud = binario.size();

    for (int i = 0; i < longitud; i += n) {
        string bloque = binario.substr(i, n);  // Extraemos el bloque de n bits

        // Si es el primer bloque, invertimos todos los bits
        if (i == 0) {
            invertirBits(bloque, 1);
        } else {
            // Contamos los 1s y 0s en el bloque anterior
            string bloqueAnterior = binario.substr(i - n, n);
            int unos = 0, ceros = 0;
            contarBits(bloqueAnterior, unos, ceros);

            // Aplicar reglas de inversión basadas en el bloque anterior
            if (unos == ceros) {
                invertirBits(bloque, 1);  // Invertir todos los bits
            } else if (ceros > unos) {
                invertirBits(bloque, 2);  // Invertir cada 2 bits
            } else {
                invertirBits(bloque, 3);  // Invertir cada 3 bits
            }
        }

        binarioCodificado += bloque;  // Añadir el bloque codificado al resultado final
    }

    return binarioCodificado;
}

// Función que realiza el segundo método de codificación
string codificarMetodo2(const string &binario, int n) {
    string binarioCodificado = "";
    int longitud = binario.size();

    for (int i = 0; i < longitud; i += n) {
        string bloque = binario.substr(i, n);  // Extraemos el bloque de n bits
        string bloqueCodificado(bloque.size(), '0');  // Crear un string temporal para almacenar el bloque desplazado

        // Aplicar desplazamiento circular de bits
        for (size_t j = 0; j < bloque.size(); j++) {
            bloqueCodificado[j] = bloque[(j + bloque.size() - 1) % bloque.size()];  // Desplazamiento circular
        }

        binarioCodificado += bloqueCodificado;  // Añadir el bloque codificado
    }

    return binarioCodificado;
}

// Función que convierte una cadena binaria a un carácter
char convertirBinarioAChar(const string &binario) {
    char valor = 0;
    for (size_t i = 0; i < 8; i++) {
        valor = valor * 2 + (binario[i] - '0');
    }
    return valor;
}

// Función que genera un archivo binario con la codificación
void generarArchivoBinario(const string &binarioCodificado, const string &archivoSalida) {
    ofstream archivoBinario(archivoSalida, ios::binary);

    if (!archivoBinario.is_open()) {
        cout << "Error al abrir el archivo de salida." << endl;
        return;
    }

    // Convertir binario a bytes y escribir en el archivo binario
    for (size_t i = 0; i < binarioCodificado.size(); i += 8) {
        string bloque = binarioCodificado.substr(i, 8);
        if (bloque.size() < 8) {
            // Si el bloque no tiene 8 bits, completamos con ceros
            bloque.append(8 - bloque.size(), '0');
        }
        char byte = convertirBinarioAChar(bloque);
        archivoBinario.write(&byte, sizeof(char));
    }

    archivoBinario.close();
}

int main() {
    int n, metodo;
    string archivoTexto, archivoSalida;

    // Ingresar la semilla y método
    cout << "Ingresa la semilla (n) para dividir los bloques: ";
    cin >> n;

    cout << "Selecciona el método de codificación (1 o 2): ";
    cin >> metodo;

    // Pedimos el nombre del archivo de entrada
    cout << "Ingresa el nombre del archivo de texto fuente (sin la extensión .txt): ";
    cin >> archivoTexto;
    archivoTexto += ".txt";  // Agregar extensión al nombre del archivo

    // Pedimos el nombre del archivo de salida
    cout << "Ingresa el nombre del archivo de salida binario: ";
    cin >> archivoSalida;

    // Leemos el archivo de texto
    ifstream archivo(archivoTexto);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo fuente." << endl;
        return 1;
    }

    // Convertir el contenido del archivo a binario
    string binario = "";
    char caracter;
    while (archivo.get(caracter)) {
        convertirCaracterABinario(caracter, binario);
    }
    archivo.close();

    cout << "Archivo en binario: " << binario << endl;

    // Rellenar el último bloque si no tiene suficientes bits
    if (binario.size() % n != 0) {
        int bitsFaltantes = n - (binario.size() % n);
        binario.append(bitsFaltantes, '0');  // Agregar ceros al final del binario
    }

    // Codificar el archivo en binario según el método seleccionado
    string binarioCodificado;
    if (metodo == 1) {
        binarioCodificado = codificarMetodo1(binario, n);
    } else if (metodo == 2) {
        binarioCodificado = codificarMetodo2(binario, n);
    } else {
        cout << "Método de codificación no válido." << endl;
        return 1;
    }

    cout << "Archivo codificado en binario: " << binarioCodificado << endl;

    // Generar el archivo binario de salida
    generarArchivoBinario(binarioCodificado, archivoSalida);

    cout << "Archivo binario generado exitosamente en: " << archivoSalida << endl;

    return 0;
}
