#include <iostream>
#include <vector>

using namespace std;

vector<string> split(string texto, char separador) {
    vector<string> resultado;
    string palabra="";
    for (char ch : texto) {
        if (ch != separador) {
            palabra+=ch;
        }
        else {
            resultado.push_back(palabra);
            palabra="";
        }
    }
    return resultado;
}


vector<string> split_avanzado(string texto, char separador) {
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