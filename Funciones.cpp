#include "Funciones.h"
#include <fstream>
#include <iostream>

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

vector<vector<string>> fill_database() {
    vector<vector<string>> lines;
    ifstream data("../mpst_full_data_fixed.csv");
    if (!data.is_open()) {
        cerr << "Error: No se pudo abrir el archivo" << endl;
        return lines;
    }
    string line = "";
    getline(data, line);
    while (getline(data, line)) {
        lines.push_back(split_avanzado(line,';'));
    }
    data.close();
    return lines;
}

vector<string> get_col(vector<vector<string>> database, int pos) {
    vector<string> ret;
    for (auto& i : database) {
        if (pos < i.size()) {
            ret.push_back(i[pos]);
        }
    }
    return ret;
}
