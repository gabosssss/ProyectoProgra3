#include <iostream>
#include <vector>

using namespace std;

vector<string> split(string texto, char separador) {
    vector<string> resultado;
    char delimitador = '"';
    string palabra="";
    bool dentroDeComillas = false;
    for (char ch : texto) {
        if (ch == delimitador) {
            dentroDeComillas = !dentroDeComillas;
        } else if (ch == separador && !dentroDeComillas) {
            resultado.push_back(palabra);
            palabra = "";
        } else {
            palabra += ch;
        }
    }
    if (!palabra.empty()) {
        resultado.push_back(palabra);
    }

    return resultado;
}