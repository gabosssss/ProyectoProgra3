#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include "Objetos/Peliculas.cpp"
#include "Objetos/Usuario.h"
#include "Funciones.cpp"

using namespace std;

int main() {
    ifstream data;
    ifstream data2;
    data.open("../mpst_full_data_fixed.csv");
    string line;
    vector<vector<string>> peliculas;
    getline(data,line);
    while (getline(data,line)) {
        vector<string> pelis=split(line,';');
        peliculas.push_back(pelis);
    }

    data.close();

    for (size_t i = 0; i < peliculas.size(); i++) {
        for (size_t j = 0; j < peliculas[i].size(); j++) {
            cout << peliculas[i][j] <<endl;
        }
        cout << endl;
    }
}