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
    data.open("../mpst_full_data.csv");
    string line="";
    getline(data,line);
    getline(data,line);

    cout<<line<<endl<<endl;

    vector<string> hola=split(line,',');
    for (int i=0;i<hola.size();i++) {
        cout<<hola[i]<<endl;
    }

    data.close();
}
